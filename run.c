#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "rdwr.h"
#include "tools.h"

char file_name[256];
int block_size, block_count;
int flag;

int main(int argc, char *argv[]){
  if(argc < 5){
    char err[] = "Error: Do not have enough parameters!\n";
    write(2, err, sizeof(err));
    return 0;
  }

  strcpy(file_name, argv[1]);

  if(argv[2][0] != '-'){
    char err[] = "Error: No read/write parameter!\n";
    write(2, err, sizeof(err));
    return 0;
  }
  if(argv[2][1] == 'r')
    flag = 0;
  else flag = 1;

  block_size = stringtoint(argv[3]);
  if(block_size == -1){
    char err[] = "Error: Unvalid Block_size!\n";
    write(2, err, sizeof(err));
    return 0;
  }

  block_count = stringtoint(argv[4]);
  if(block_count == -1){
    char err[] = "Error: Unvalid Block_count!\n";
    write(2, err, sizeof(err));
    return 0;
  }

  double start_time = now();

  if(flag == 0){
    block_read(file_name, block_size, block_count);
  }else{
    block_write(file_name, block_size, block_count);
  }

  double finish_time = now();

  printf("Runtime: %lf s\n", finish_time-start_time);
  printf("Runtime: %lf MiBps\n", block_count/1024/1024*block_size/(finish_time-start_time));
  return 0;
}