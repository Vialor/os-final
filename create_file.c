#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rdwr.h"

const int Rea_Size = 167772160;
const int block_size = 1<<12, block_count = 5<<13;
char File_name[] = "test_file.txt";

int main(){
  int fd = open(File_name, O_WRONLY | O_CREAT | O_TRUNC);
  if(fd < 0){
    char err[] = "Error: File Open Failed\n";
    write(2, err, sizeof(err));
    return;
  }

  block_write(File_name, block_size, block_count);
  return 0;
}