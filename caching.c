#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdlib.h>
#include "rdwr.h"

const int block_count = 8388608;
int block_size = 4098;
char File_name[] = "./test/32G.txt";
double start_time, finish_time;

double now() {
  struct timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main(){

  start_time = now();
  block_read(File_name, block_size, block_count);
  finish_time = now();
  printf("First Read Runtime: %.6lf\n", finish_time-start_time);
  
  start_time = now();
  block_read(File_name, block_size, block_count);
  finish_time = now();
  printf("Again Read Runtime: %.6lf\n", finish_time-start_time);

  return 0;
}