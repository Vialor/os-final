#include <sys/time.h>
#include <string.h>

double now() {
  struct timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec + tv.tv_usec / 1000000.0;
}

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