# Lab 1: Unix utilities (`util`)

User-space programs for xv6 built on its system calls (fork, exec, pipes, file I/O). Part of my [MIT 6.1810 labs](https://github.com/pjflukky/xv6-labs). Starter code © MIT PDOS.

| Exercise | What it does | Status |
|----------|--------------|--------|
| [sleep](../user/sleep.c) | Pauses for N timer ticks | ✅ |
| [sixfive](../user/sixfive.c) | Prints numbers in files or stdin that are multiples of 5 or 6 | ✅ |
| [memdump](../user/memdump.c) | Prints a block of memory field by field, following a format string | ✅ |
| [primes](../user/primes.c) | Prime sieve using a chain of processes and pipes | ⬜ |
| [find](../user/find.c) | Searches a directory tree recursively | ⬜ |
| [xargs](../user/xargs.c) | Runs a command once per line of stdin | ⬜ |

## Run

```bash
git clone https://github.com/pjflukky/xv6-labs.git && cd xv6-labs
git checkout util
make qemu          # boots xv6. Try: sleep 10. Quit: Ctrl-a x
./grade-lab-util   # runs the tests
```

Requires a RISC-V toolchain and QEMU ([setup](https://pdos.csail.mit.edu/6.1810/2025/tools.html)).

## Notes

**sleep:** validates the argument, prints usage errors to stderr, and calls the `pause` syscall (newer xv6's name for sleep-by-ticks). Learned how a user call goes through the `usys.S` stub and `ecall` to `sys_pause` in the kernel, and how `user.h` declarations are linked against `ULIB`.

**sixfive:** a streaming parser that reads input in chunks with `read()` and tracks per-token state, so numbers that span chunk boundaries and a last line with no newline are both handled. Reads stdin when given no files, and reports missing files the way `cat` does. Learned why `read()` must be looped and why `(fd = open(...)) < 0` needs the extra parentheses.

**memdump:** I implemented the `memdump()` function only. `main()` and its examples are provided starter code that calls it. The function walks a byte buffer one field at a time, using a format string (int, short, char, pointer, string pointer, inline string), and checks the remaining length before each read. Learned the difference between `s` and `&s` for `char *s` vs `char s[]`: memdump takes the address of the bytes to decode, so a `char *` field needs two hops (`&s` → `s` → characters). Also learned how to read typed values out of raw bytes with casts like `*(uint64 *)data` and `*(char **)data`, how struct fields are laid out and padded on RV64, and why the inline-string case should look for `'\0'` only within the remaining length and measure the string before advancing the pointer.
