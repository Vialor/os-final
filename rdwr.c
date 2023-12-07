#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void block_read(char* file_name, int block_size, int block_count)
{
  int fd = open(file_name, O_RDONLY);
  if(fd <= 0){
    printf("Error: File Open Failed\n");
    return;
  }
  char buf[block_size];
  for(int i=0; i<block_count; i++)
    read(fd, buf, block_size);
  close(fd);
}


void block_write(char* file_name, int block_size, int block_count)
{
  int fd = open(file_name, O_RDWR|O_CREAT|O_TRUNC);
  if(fd<=0){
    char err[] = "Error: File Open Failed\n";
    write(2, err, sizeof(err));
    return;
  }
  char buf[block_size];
  for(int i=0;i<block_size; i++)
    buf[i]=48;
  buf[block_size-1]='\n';
  for(int i=0; i<block_count; i++)
    write(fd, buf, block_size);
  close(fd);
}