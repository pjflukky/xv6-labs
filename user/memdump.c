#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void memdump(char *fmt, char *data, int len);

int
main(int argc, char *argv[])
{
  if (argc == 1) {
    printf("Example 1:\n");
    int a[2] = {61810, 2026};
    memdump("ii", (char *)a, sizeof(a));

    printf("Example 2:\n");
    memdump("S", "a string", sizeof("a string"));

    printf("Example 3:\n");
    char *s = "another";
    memdump("s", (char *)&s, sizeof(s));

    struct sss {
      char *ptr;
      int num1;
      short num2;
      char byte;
      char bytes[8];
    } example;

    example.ptr = "hello";
    example.num1 = 1819438967;
    example.num2 = 100;
    example.byte = 'z';
    strcpy(example.bytes, "xyzzy");

    printf("Example 4:\n");
    memdump("pihcS", (char *)&example, sizeof(example));

    printf("Example 5:\n");
    memdump("sccccc", (char *)&example, sizeof(example));
  } else if (argc == 2) {
    // format in argv[1], up to 512 bytes of data from standard input.
    char data[512];
    int n = 0;
    memset(data, '\0', sizeof(data));
    while (n < sizeof(data)) {
      int nn = read(0, data + n, sizeof(data) - n);
      if (nn <= 0)
        break;
      n += nn;
    }
    memdump(argv[1], data, n);
  } else {
    printf("Usage: memdump [format]\n");
    exit(1);
  }
  exit(0);
}

void
memdump(char *fmt, char *data, int len)
{
  // Your code here.  `data` holds `len` valid bytes.
  while (*fmt != '\0') {
    switch (*fmt) {
    default:
      fprintf(2, "Not a Valid format\n");
      return;

    case 'i':
      if (len < sizeof(int)) {
        fprintf(2, "memdump: not enough data for 'i'\n");
        return;
      }
      fprintf(1, "%d\n", *(int *)data);
      data = data + sizeof(int);
      len -= sizeof(int);
      break;

    case 'p':
      if (len < sizeof(long)) {
        fprintf(2, "memdump: not enough data for 'p'\n");
        return;
      }
      fprintf(1, "%lx\n", *(long *)data);
      data = data + sizeof(long);
      len -= sizeof(long);
      break;

    case 'h':
      if (len < sizeof(short)) {
        fprintf(2, "memdump: not enough data for 'h'\n");
        return;
      }
      fprintf(1, "%d\n", *(short *)data);
      data = data + sizeof(short);
      len -= sizeof(short);
      break;

    case 'c':
      if (len < sizeof(char)) {
        fprintf(2, "memdump: not enough data for 'c'\n");
        return;
      }
      fprintf(1, "%c\n", *(char *)data);
      data = data + sizeof(char);
      len -= sizeof(char);
      break;

    case 's':
      if (len < sizeof(long)) {
        fprintf(2, "memdump: not enough data for 's'\n");
        return;
      }
      fprintf(1, "%s\n", *(char **)data);
      data = data + sizeof(long);
      len -= sizeof(long);
      break;

    case 'S':
      if (len < strlen(data)) {
        fprintf(2, "memdump: not enough data for 'S'\n");
        return;
      }
      fprintf(1, "%s\n", data);
      len -= strlen(data) + 1;
      data = data + strlen(data) + 1;
      break;
    }
    fmt++;
  }
}
