#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdlib.h>
#include "rdwr.h"

const int Rea_Size = 167772160;
int block_size = 1024, block_count;
char File_name[] = "test_file.txt";
double start_time, finish_time;

double now() {
  struct timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main(){

  start_time = now();
  block_read(File_name, block_size, Rea_Size/block_size);
  finish_time = now();
  printf("First Read Runtime: %.6lf\n", finish_time-start_time);
  
  start_time = now();
  block_read(File_name, block_size, Rea_Size/block_size);
  finish_time = now();
  printf("Again Read Runtime: %.6lf\n", finish_time-start_time);

  return 0;
}