#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rdwr.h"

const int Rea_Size = 167772160;
const int MiB = 1<<20;
int block_size = 1, block_count;
char File_name[] = "test_file.txt";
int start_time, finish_time;

int main(){

  start_time = time(NULL);
  block_read(File_name, block_size, Rea_Size/block_size);
  finish_time = time(NULL);

  double MiBps = (double)Rea_Size / (double)MiB / (double)(finish_time-start_time);
  printf("MiB/s when block_size=1 : %.6lf\n", MiBps );

  double Bps = (double)Rea_Size / (double)(finish_time-start_time);
  print("Number of System Calls in 1 second: %.6lf\n", Bps);

  
  return 0;
}