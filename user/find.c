#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "kernel/param.h"

// structs
struct exec_opt {
  char *exec_argv[MAXARG];
  int exec_argc;
  int isExec;
};

//variables
char
  buf[512]; // EDITED: makes buff global so each recursion doesn't add new buf
struct exec_opt eo;

// methods
void find(char *name);
void usage();
void exec_overbound();

void
find(char *name)
{
  char *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(buf, O_RDONLY)) < 0) {
    fprintf(2, "can't find %s\n", buf);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "find: cannot stat %s\n", buf);
    close(fd);
    return;
  }

  // check buf size
  if (strlen(buf) + 1 + DIRSIZ + 1 > sizeof(buf)) { // EDITED: add DIRSIZ
    printf("find: buf too long\n");
    close(fd); // EDITED: forgot to close fd
    return;
  }

  p = buf + strlen(buf);
  *p++ = '/';
  // iterate through the directory
  while (read(fd, &de, sizeof(de)) > 0) {
    if (de.inum == 0)
      continue;
    if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
      continue;

    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;
    if (
      strcmp(p, name) ==
      0) { // EDITED: was comparing with de.name, which has no null terminator;
      if (eo.isExec == 1) {
        if (fork() == 0) {
          eo.exec_argv[eo.exec_argc] = buf;
          eo.exec_argc++;
          eo.exec_argv[eo.exec_argc] = 0;
          exec(eo.exec_argv[0], eo.exec_argv);
        } else {
          wait(0);
        }
      } else {
        printf("%s\n", buf);
        // EDITED: had continue but should not, since the matching might be a directory
      }
    }

    if (stat(buf, &st) >= 0 && st.type == T_DIR) {
      find(name);
      continue;
    } else {
      continue;
    }
  }

  close(fd);
}

int
main(int argc, char *argv[])
{

  char *name;
  int npos = 0;

  // find flag
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-exec") == 0) {
      if (i + 1 >= argc)
        usage();
      eo.exec_argc = argc - (i + 1);
      eo.isExec = 1;
      if (eo.exec_argc + 1 > MAXARG)
        exec_overbound();
      for (int j = 0; j < eo.exec_argc; j++) {
        eo.exec_argv[j] = argv[i + 1 + j];
      }
      break;
    } else {
      npos++;
    }
  }

  if (npos == 1) {
    strcpy(buf, ".");
    name = argv[1];
  } else if (npos == 2) {
    strcpy(buf, argv[1]);
    name = argv[2];
  }

  else
    usage();
  find(name);
  exit(0);
}

void
usage()
{
  fprintf(2, "Invalid; USAGE: find <dir> <name> -flag <cmd>\n");
  exit(1);
}

void
exec_overbound()
{
  fprintf(2, "argument too long to exec\n");
  exit(1);
}
