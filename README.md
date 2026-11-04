# MIT 6.1810 (xv6 on RISC-V): Lab Solutions

Self-study of MIT's 6.1810 Operating System Engineering.
Starter code © MIT PDOS; my solutions are on the lab branches below.

| Lab | Branch | Topics | Status |
|-----|--------|--------|--------|
| Unix utilities | [util](https://github.com/pjflukky/xv6-labs/tree/util) | fork, exec, pipes, file system | 🚧 |
| System calls | [syscall](https://github.com/pjflukky/xv6-labs/tree/syscall) | trap path, syscall table | ⬜ |
| Page tables | [pgtbl](https://github.com/pjflukky/xv6-labs/tree/pgtbl) | virtual memory | ⬜ |
| Traps | [traps](https://github.com/pjflukky/xv6-labs/tree/traps) | interrupts, backtrace | ⬜ |
| Copy-on-write | [cow](https://github.com/pjflukky/xv6-labs/tree/cow) | page faults, refcounts | ⬜ |
| Networking | [net](https://github.com/pjflukky/xv6-labs/tree/net) | NIC driver | ⬜ |
| Locks | [lock](https://github.com/pjflukky/xv6-labs/tree/lock) | contention, allocators | ⬜ |


## Running
git clone https://github.com/pjflukky/xv6-labs
git checkout util
make qemu
