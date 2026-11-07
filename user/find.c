#include "kernel/types.h"
#include "kernel/stat.h" 
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"


void find(char *path, char *name){
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;
  
  if((fd = open(path, O_RDONLY)) < 0){
    fprintf(2, "can't find %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  // check if path is a directory
  if(st.type != T_DIR){
    fprintf(2, "wrong st.type; should be a Directory");
    close(fd);  
    return;
  }

  // check path size
  if(strlen(path) + 1 + 1 > sizeof(buf)){
    printf("find: path too long\n");
    return;
  }
  
  strcpy(buf, path);
  p = buf + strlen(buf);
  *p++ = '/';
  // iterate through the directory
  while(read(fd, &de, sizeof(de))){
    if(de.inum == 0)
      continue;
    if(strcmp(de.name,".") == 0 || strcmp(de.name,"..") == 0) 
      continue;
              
    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;
    if(strcmp(de.name, name) == 0){
      printf("%s\n", buf);
      continue;
    }
    else if(stat(buf, &st) >= 0){
      find(buf, name);   
      continue;
    }
    else{
      continue;
    }
 
  }

  close(fd);
}

int main(int argc, char *argv[]){

  if(argc == 2){
    find(".",argv[1]);
  }
  else if(argc == 3){
    find(argv[1], argv[2]);
  }
  else{
    fprintf(2, "find USAGE: find <path> <filename>");
    exit(1);
  }

  exit(0);
}



