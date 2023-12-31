#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include "rdwr.h"

#define num_threads 16

const int MiB = 1<<20;
int block_size = 1<<13;
char file_name[256];
double start_time, finish_time;
unsigned int res[num_threads];
long long filesize = 0;

double now() {
  struct timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec + tv.tv_usec / 1000000.0;
}

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

  int size;

  //Use lseek to jump to numth block
  if(lseek(fd, num*block_size, SEEK_SET) == -1){
    close(fd);
    pthread_exit(NULL);
  }
  int step = (num_threads-1)*block_size;
  char buf[block_size];

  while(1){
    size = read(fd, buf, block_size);
    //If size isn't a multiple of 4, fill the dif
    if(size/4 != (size+3)/4){
      printf("Need to add zero, size = %d\n",size);
      int dif = 4-size%4;
      for(int i=0; i<dif; i++)
        buf[size+i] = '\0';
      size += dif;
    }
    //Transfer buf to unsigned int*
    res[num] ^= XOR((unsigned int *)buf, size/4);
    //res[num] = XOR((unsigned int *)buf, (size+3)/4);
    //printf("num: %d, res: %u\n", num, res[num]);

    filesize += size;
    
    if(size < block_size){
      close(fd);
      pthread_exit(NULL);
    }
    //skip the blocks belong to other threads
    if(lseek(fd, step, SEEK_CUR) == -1){
      close(fd);
      pthread_exit(NULL);
    }
  }
}

int main(int argc, char *argv[]){
  if(argc<2){
    char err[] = "Error: Do not have enough parameters!\n";
    write(2, err, sizeof(err));
    return 0;
  }
  strcpy(file_name, argv[1]);

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

  printf("Block_size = %d\n",block_size);
  printf("Number of threads: %d\n",num_threads);
  printf("Runtime totally: %lf\n", finish_time-start_time);
  printf("MiB per second: %lf\n", (double)filesize / (double) MiB / (finish_time-start_time));

  unsigned int ans = 0;
  for(int i=0; i<num_threads; i++)
    ans ^= res[i];
  printf("XOR of the File Decimal: %u\n",ans);
  printf("XOR of the File Hex: %08x\n",ans);
  
  return 0;
}
