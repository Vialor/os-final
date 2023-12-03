#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>


char file_name[256];
int block_size, block_count;
int flag, fd;

int stringtoint(char *s){
  int len = strlen(s);
  int res = 0;
  for(int i=0; i<len; i++){
    if(s[i]<48 || s[i]>57)
      return -1;
    res = res*10 + s[i]-48;
  }
  return res;
}

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

  double start_time = time(NULL)/3600;

  if(flag == 0){
    fd = open(file_name, O_RDONLY);
    if(fd<=0){
      char err[] = "Error: File Open Failed\n";
      write(2, err, sizeof(err));
      return 0;
    }
    char buf[block_size];
    for(int i=0; i<block_count; i++)
      read(fd, buf, block_size);
    close(fd);
      
  }else{
    fd = open(file_name, O_RDWR|O_CREAT|O_TRUNC);
    if(fd<=0){
      char err[] = "Error: File Open Failed\n";
      write(2, err, sizeof(err));
      return 0;
    }
    char buf[block_size];
    for(int i=0;i<block_size; i++)
      buf[i]=48;
    buf[block_size-1]='\n';
    for(int i=0; i<block_count; i++)
      write(fd, buf, block_size);
    close(fd);
  }

  double finish_time = time(NULL)/3600;

  write(2, "Runtime: %lf\n", finish_time-start_time);
  return 0;
}