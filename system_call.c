#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include "rdwr.h"

const int Rea_Size = 167772160 >> 3;
const int MiB = 1<<20;
int block_size = 1, block_count;
char File_name[] = "test_file.txt";
int file_size = 1<<20;
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

  double MiBps = (double)Rea_Size / (double)MiB / (finish_time-start_time);
  printf("MiB/s when block_size=1 : %.6lf\n", MiBps );

  double Bps = (double)Rea_Size / (finish_time-start_time);
  print("Number of read in 1 second: %.6lf\n", Bps);

  
  //Test of lseek
  int fd;
  while((fd = open(File_name, O_RDONLY) ) <1);
  srand(time(NULL));
  start_time = now();
  for(int i=0; i<Rea_Size; i++)
    lseek(fd, rand()%file_size, SEEK_SET);
  finish_time = now();
  Bps = (double)Rea_Size / (finish_time-start_time);
  print("Number of lseek in 1 second: %.6lf\n", Bps);
  close(fd);
  return 0;
}