#include "kernel/types.h"
#include "kernel/stat.h" 
#include "user/user.h"
#include "kernel/fcntl.h"

/*
 * flush the token, dump if invalid (0) 
 */
void flush(int* num, int* valid){
  if(*valid == 1 && (*num % 5 == 0 || *num % 6 == 0)){
    fprintf(1, "%d\n", *num);
  }
  *num = 0;
  *valid = 1;
}

void sixfive(int fd){
  char buf[512];
  int  n;
  int num = 0;
  int valid = 1;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(int i=0; i<n; i++){
      char c = buf[i];
      if(c >= '0' && c <= '9'){ 
        num = 10*num + (c-'0'); 
      }
      else if (c != '\0' || strchr(" -\r\t\n./,", c) != 0){
        flush(&num, &valid);
      }
      else{ // non number or seperator
        valid = 0; 
      }

    }
  }

  //last flush for leftover token
  flush(&num, &valid);

}


int main(int argc, char* argv[]){
  if(argc < 2){
    sixfive(0);            // no files → read stdin
    exit(0);
  }

  for(int i = 1; i < argc; i++){
    int fd;
    if((fd = open(argv[i], O_RDONLY)) < 0){
      fprintf(2, "sixfive: cannot open %s\n", argv[i]);
      exit(1);
    }
    sixfive(fd);
    close(fd);
  }
  exit(0);
}
