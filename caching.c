#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rdwr.h"
#include "tools.h"

const int block_size = 131072;
const int block_count = (1<<30) / block_size * 4;
int file_size = block_count / 1024 * block_size / 1024; // MB
char file_name[] = "./test/4G.txt";
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