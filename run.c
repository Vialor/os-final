#include <stdio.h>
#include <string.h>
#include <unistd.h>


char file_name[256];


int main(int argc, char *argv[]){
  if(argc < 5){
    char err[] = "Error: Do not have enough parameters!\n";
    write(2, err, sizeof(err));
    return 0;
  }
  strcpy(file_name, argv[1]);
  

  return 0;
}