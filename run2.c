#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rdwr.h"


char file_name[256];
int block_size;
long long block_count;
int flag, fd;

int stringtoint(char *s){
  int len = strlen(s);
  int res = 0;
  for(int i=0; i<len; i++){
    if(s[i]<48 || s[i]>57)
      return -1;
    res = res*10 + s[i]-48;
  }
  return res;
}

int main(int argc, char *argv[]){
  if(argc < 3){
    char err[] = "Error: Do not have enough parameters!\n";
    write(2, err, sizeof(err));
    return 0;
  }

  strcpy(file_name, argv[1]);

  block_size = stringtoint(argv[2]);
  if(block_size == -1){
    char err[] = "Error: Unvalid Block_size!\n";
    write(2, err, sizeof(err));
    return 0;
  }

  block_count = 1;

  int start_time, finish_time, runtime;

  while(1){
    start_time = time(NULL);
    block_read(file_name, block_size, block_count);
    finish_time = time(NULL);
    runtime = finish_time-start_time;
    if(runtime >= 5)
      break;
    block_count <<= 1;
  }

  long long file_size = block_count * (long long)block_size;
  printf("block_count: %lld, block_size: %d B\n", block_count, block_size);
  printf("File Size: %lld Bytes, %lld MB\n", file_size, file_size >> 20);
  printf("Process Speed: %lld B/s, %lld MiB/s\n", file_size/runtime, (file_size/runtime) >> 20);
  return 0;
}