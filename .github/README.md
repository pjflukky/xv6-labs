# Lab 1: Unix utilities (`util`)

User-space programs for xv6 built on its system calls (fork, exec, pipes, file I/O). Part of my [MIT 6.1810 labs](https://github.com/pjflukky/xv6-labs). Starter code © MIT PDOS.

| Exercise | What it does | Status |
|----------|--------------|--------|
| [sleep](../user/sleep.c) | Pauses for N timer ticks | ✅ |
| [pingpong](../user/pingpong.c) | Sends a byte between two processes over pipes | ⬜ |
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
