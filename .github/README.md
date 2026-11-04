# Lab: Unix utilities (util)

Part of my [MIT 6.1810 xv6 labs](https://github.com/pjflukky/xv6-labs).
Starter code © MIT PDOS. My work is in the files below.

| Exercise | File | Status |
|----------|------|--------|
| sleep    | user/sleep.c    | ✅ |
| pingpong | user/pingpong.c | ⬜ |
| primes   | user/primes.c   | ⬜ |
| find     | user/find.c     | ⬜ |
| xargs    | user/xargs.c    | ⬜ |

## Notes
### sleep
- Uses the `pause` syscall (renamed from `sleep` in newer xv6); units are ticks (~0.1s).
- ...

## Run
make qemu
./grade-lab-util
