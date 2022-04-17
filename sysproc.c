#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_pgtPrint(void)
{
  struct proc *cur_proc = myproc();
  pde_t *pg_dir = cur_proc->pgdir;
  uint count = 0;
  // uint flag = 0;
  for (uint i = 0; i < NPDENTRIES; i++)
  {
    pde_t pg_dir_entry = pg_dir[i]; // pg_dir_entry: Physical address of the page table
    if (pg_dir_entry & PTE_P)       // Validity of the page directory entry
    {
      uint *pg_table = (uint *)P2V(PTE_ADDR(pg_dir_entry));
      for (uint j = 0; j < NPTENTRIES; j++)
      {
        pte_t pg_table_entry = pg_table[j];
        if ((pg_table_entry & PTE_P) && (pg_table_entry & PTE_U))
        {
          cprintf("%d %d\n", i, j);
          cprintf("Entry No.: %d, Virtual Address: %p, Physical Address: %p\n", count + 1, (&pg_table_entry), &pg_table_entry);
          count++;
        }
      }
    }
  }
  cprintf("%d\n", count);
  return count;
}
