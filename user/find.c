#include "kernel/types.h"
#include "kernel/stat.h" 
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"

char buf[512]; // EDITED: makes buff global so each recursion doesn't add new buf

void find(char *name){
  char *p;
  int fd;
  struct dirent de;
  struct stat st;
  
  if((fd = open(buf, O_RDONLY)) < 0){
    fprintf(2, "can't find %s\n", buf);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", buf);
    close(fd);
    return;
  }

  // check buf size
  if(strlen(buf) + 1 + DIRSIZ + 1 > sizeof(buf)){ // EDITED: add DIRSIZ
    printf("find: buf too long\n"); 
    close(fd); // EDITED: forgot to close fd
    return;
  }
  
   p = buf + strlen(buf);
  *p++ = '/';
  // iterate through the directory
  while(read(fd, &de, sizeof(de)) > 0){
    if(de.inum == 0)
      continue;
    if(strcmp(de.name,".") == 0 || strcmp(de.name,"..") == 0) 
      continue;
              
    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;
    if(strcmp(p, name) == 0){ // EDITED: was comparing with de.name, which has no null terminator; 
      printf("%s\n", buf);
      // EDITED: had continue but should not, since the matching might be a directory
    }

    if(stat(buf, &st) >= 0 && st.type == T_DIR){
      find(name);   
      continue;
    }
    else{
      continue;
    }
 
  }

  close(fd);
}

int main(int argc, char *argv[]){

  char *start, *name;
  if(argc == 2){
    start = ".";
    name = argv[1];
  }
  else if(argc == 3){
    start = argv[1];
    name = argv[2];
  }
  else{
    fprintf(2, "find USAGE: find <buf> <filename>");
    exit(1);
  }

  if(strlen(start) > sizeof(buf)){
    fprintf(2, "argument size too large");
    exit(1);
  }

  strcpy(buf, start);
  find(name);

  exit(0);
}



