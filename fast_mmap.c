#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <pthread.h>
#include "rdwr.h"
#include "tools.h"

#define num_threads 16
#define ll long long

const int MiB = 1<<20;
int block_size = 4096;
char file_name[256];
double start_time, finish_time;
unsigned int res[num_threads];
ll filesize = 0;

unsigned int XOR(unsigned int *A, int size){
  unsigned int res = 0;
  for(int i=0; i<size; i++){
    /*
    unsigned int val = 0;
    for(int j=i; j<i+4; j++)
      val = val*256 + A[j];
    res ^= val;
    */
    res ^= (unsigned int)A[i];
  }
  return res;
}

void* apply_read(void *arg){
  int num = *(int *)arg;
  int fd = open(file_name, O_RDONLY);
  if(fd<0){
    printf("File Open Failed!\n");
    pthread_exit(NULL);
  }

  ll pos = num*block_size;
  if(lseek(fd, num*block_size, SEEK_SET) == -1){
    printf("lseek Failed\n");
    close(fd);
    pthread_exit(NULL);
  }
  int step = (num_threads-1)*block_size;
  char *buf;

  while(1){
    int size = block_size;
    if(filesize-pos < block_size)
      size = filesize-pos;
    buf = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, pos);

    if(buf == MAP_FAILED){
      //printf("Error mapping file to memory\n");
      close(fd);
      pthread_exit(NULL);
    }

    if(size/4 != (size+3)/4){
      printf("Need to add zero, size = %d\n",size);
      int dif = 4-size%4;
      for(int i=0; i<dif; i++)
        buf[size+i] = '\0';
      size += dif;
    }
    res[num] ^= XOR((unsigned int *)buf, size/4);
    //printf("num: %d, res: %u\n", num, res[num]);

    if(munmap(buf,size) == -1){
      printf("Error unmapping file from memory\n");
      close(fd);
      pthread_exit(NULL);
    }

    if(size < block_size){
      close(fd);
      pthread_exit(NULL);
    }
    if(lseek(fd, step, SEEK_CUR) == -1){
      printf("lseek Failed\n");
      close(fd);
      pthread_exit(NULL);
    }
    pos += num_threads*block_size;
  }
}

int main(int argc, char *argv[]){
  if(argc<2){
    char err[] = "Error: Do not have enough parameters!\n";
    write(2, err, sizeof(err));
    return 0;
  }
  strcpy(file_name, argv[1]);

  int fd = open(file_name, O_RDONLY);
  if(fd<0){
    printf("File Open Failed!\n");
    return 0;
  }
  struct stat file_stat;
  if (fstat(fd, &file_stat) == -1) {
    perror("Error getting file size");
    close(fd);
    exit(EXIT_FAILURE);
  }
  filesize = (ll)file_stat.st_size;
  close(fd);

  pthread_t *threads;
  threads = (pthread_t *) malloc(sizeof(pthread_t)*num_threads);
  if (!threads) {
    char err[] = "out of memory allocating thread handles";
    write(2, err, sizeof(err));
    return 0;
  }

  start_time = now();

  for(int i=0; i<num_threads; i++) {
    int *arg = malloc(sizeof(*arg));
    *arg = i;
    pthread_create(&threads[i], NULL, apply_read, arg);
  }

  for(int i=0; i<num_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  finish_time = now();

  printf("Runtime: %lf\n", finish_time-start_time);
  printf("Runtime per MiB: %lf\n", (double)filesize / (double) MiB / (finish_time-start_time));

  unsigned int ans = 0;
  for(int i=0; i<num_threads; i++)
    ans ^= res[i];
  printf("XOR of the File Decimal: %u\n",ans);
  printf("XOR of the File Hex: %08x\n",ans);
  
  return 0;
}