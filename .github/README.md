# Lab 1: Unix utilities (`util`)

User-space programs for xv6 built on its system calls (fork, exec, pipes, file I/O). Part of my [MIT 6.1810 labs](https://github.com/pjflukky/xv6-labs). Starter code © MIT PDOS.

| Exercise | What it does | Status |
|----------|--------------|--------|
| [sleep](../user/sleep.c) | Pauses for N timer ticks | ✅ |
| [sixfive](../user/sixfive.c) | Prints numbers in files or stdin that are multiples of 5 or 6 | ✅ |
| [memdump](../user/memdump.c) | Prints a block of memory field by field, following a format string | ✅ |
| [find](../user/find.c) | Searches a directory tree recursively | ✅ |
| [exec](../user/find.c) | Searches a directory tree recursively; `-exec` runs a command on each match | ✅ |

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

**find:** walks the tree by reading a directory's `struct dirent` entries, building each child's path, and calling `stat` to decide whether to print it, recurse into it, or both. Skips `.` and `..` so the recursion terminates, and closes each directory's file descriptor before returning so deep trees don't exhaust xv6's per-process fd limit.

**find -exec:** `find . wc -exec echo` runs `echo ./wc` for every match. For each match, the parent forks a child, the child appends the matched path to the command's arguments and calls `exec`, and the parent `wait`s before moving on, so the output stays in order and finished children don't pile up as zombies. The command's arguments are copied out of `main`'s `argv` into an array of `MAXARG` slots inside `struct exec_opt`, so the path and the terminating `0` always fit. Writing past `argv`'s last slot overwrote the stack memory right above it, which held the `"echo"` string. The child prints an error and exits if `exec` fails, so it can't fall back into the loop as a duplicate `find`. Learned that `exec` finds the end of `argv` only by its null terminator because it takes no count, that a pointer into another array gives you none of its storage, that `fork` gives the child its own copy of globals, and that a failed `exec` returns `-1` without printing anything. Debugged it with `fprintf` before `exec` and with gdb (`display eo.exec_argv[0]@3`).
