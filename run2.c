#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>


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

char* inttostring(int x){
  char s[20];
  int len=0;
  while(x){
    s[len++] = x%10-48;
    x/=10;
  }
  for(int i=0; i<len/2; i++){
    char c=s[i];
    s[i] = s[len-i-1];
    s[len-i-1] = c;
  }
  return s;
}

int main(int argc, char *argv[]){
  if(argc < 3){
    char err[] = "Error: Do not have enough parameters!\n";
    write(2, err, sizeof(err));
    return 0;
  }

  strcpy(file_name, argv[1]);

  block_size = stringtoint(argv[2]);
  if(block_size == -1){
    char err[] = "Error: Unvalid Block_size!\n";
    write(2, err, sizeof(err));
    return 0;
  }

  block_count = 1;

  double start_time, finish_time, runtime;

  while(1){
    char s1[20], s2[20];
    snprintf(s1, 20, "%d", block_size);
    snprintf(s2, 20, "%d", block_count);
    char *run_argv[] = {
      "run",
      file_name,
      "-r",
      s1,
      s2
    };
    // strcpy(run_argv[0], "run");
    // strcpy(run_argv[1], file_name);
    // strcpy(run_argv[2], "-r");

    // snprintf(run_argv[3], sizeof(run_argv[3]), "%d", block_size);
    // snprintf(run_argv[4], sizeof(run_argv[4]), "%d", block_count);

    start_time = time(NULL)/3600;

    //execvp(file_name, (char *[]){"run", file_name, "-r", s1, s2} );
    execvp(file_name, run_argv);

    finish_time = time(NULL)/3600;

    runtime = finish_time-start_time;

    write(2, "Runtime: %lf\n", runtime);

    if(runtime>5)
      break;

    block_count <<= 1;
  }

  write(2,"File_size: %d\n", block_count*block_size);
  return 0;
}