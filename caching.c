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

int main(){
  int fd;
  while((fd = open(File_name, O_RDONLY) ) <3);

  int 
  return 0;
}