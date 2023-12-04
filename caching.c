#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rdwr.h"

const int Rea_Size = 167772160;
int block_size = 1024, block_count;
char File_name[] = "test_file.txt";
int start_time, finish_time;

int main(){

  start_time = time(NULL);
  block_read(File_name, block_size, Rea_size/block_size);
  finish_time = time(NULL);
  printf("First Read Runtime: %d\n", finish_time-start_time);
  
  start_time = time(NULL);
  block_read(File_name, block_size, Rea_size/block_size);
  finish_time = time(NULL);
  printf("First Read Runtime: %d\n", finish_time-start_time);
  
  return 0;
}