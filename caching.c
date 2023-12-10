#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rdwr.h"
#include "tools.h"

const int block_count = 8388608;
int block_size = 4098;
char File_name[] = "./test/32G.txt";
double start_time, finish_time;

int main(){
  start_time = now();
  block_read(file_name, block_size, block_count);
  finish_time = now();
  printf("First Read Runtime: %.6lf\n", finish_time-start_time);
  printf("First Read Speed: %.6lf MiBps\n", file_size/(finish_time-start_time));
  
  start_time = now();
  block_read(file_name, block_size, block_count);
  finish_time = now();
  printf("Second Read Runtime: %.6lf\n", finish_time-start_time);
  printf("Second Read Speed: %.6lf MiBps\n", file_size/(finish_time-start_time));

  return 0;
}