# Timer Interrupts: signal() vs sigaction()

## What This Program Does
This program creates timer interrupts that happen regularly. Each time an interrupt happens, the program prints the time and counts up.

## Two Ways to Handle Signals

### 1. signal() - Old Way
```c
signal(SIGALRM, interrupt_service_routine);
```
- Very simple to use - just one line of code
- Not reliable on all systems
- Might stop working after the first interrupt on some computers
- Doesn't give you much control

### 2. sigaction() - Better Way
```c
struct sigaction mysigaction;
sigemptyset(&mysigaction.sa_mask);
mysigaction.sa_handler = interrupt_service_routine;
mysigaction.sa_flags = SA_RESTART;
sigaction(SIGALRM, &mysigaction, NULL);
```
- More code but works the same on all systems
- Keeps working for all interrupts
- Gives you more control:
  - You can set flags like SA_RESTART to make interrupted system calls continue
  - You can block other signals while handling one signal
  - You can get more information about the signal

## Why Use sigaction()?
- Works more reliably
- Gives you more options
- Recommended by experts
- The old signal() function is "deprecated" (not recommended for new code)