#include <sys/cdefs.h>
#include <lib.h>
#include <unistd.h>
#include <errno.h>
#define INHERIT 1
#define NOT_INHERIT 0
#define SEM_CLOSE 1
#define SEM_UNCLOSE 0
#define SEM_UP 1
#define SEM_DOWN 0

int create_semaphore(int desc,int num1, int num2) 
{
  message m;
  m.m1_i1 = desc;
  m.m1_i2 = num1;
  m.m1_i3 = num2;
  
  _syscall(PM_PROC_NR,CREATE_SEMAPHORE, &m);
}

int up_semaphore(int desc,int num)
{
  message m;
  m.m1_i1 = desc;
  m.m1_i2 = num;
  
  _syscall(PM_PROC_NR,UP_SEMAPHORE, &m);
}
