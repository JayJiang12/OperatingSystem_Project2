#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>

extern int processID;
extern long * syscall_list;
extern int allow;
extern int count;

void set_PID(int PID);
int get_PID(void);
void set_syscall_list(void);
long get_syscall_list(void);
void set_allow(int bool);
int get_allow(void);
int get_count(void);

void set_PID(int PID){

  processID = PID;
}

int get_PID(void){

  return processID;
}

void set_syscall_list(void){

  syscall_list = (long*)kmalloc(sizeof(long), GFP_KERNEL);
}

long * get_syscall_list(void){
  
  return syscall_list;
}

void set_allow(int bool){

  allow = bool;
}

int get_allow(void){

  return allow;
}

int get_count(void){
  return count;
}
