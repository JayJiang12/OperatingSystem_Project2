#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>

int processID;
unsigned long * syscall_list;
int allow;
int count_process;

asmlinkage void sys_set_PID(int PID){

  processID = PID;
}

asmlinkage int sys_get_PID(void){

  return processID;
}

asmlinkage void sys_set_syscall_list(void){

  syscall_list = (unsigned long*)kmalloc(sizeof(unsigned long), GFP_KERNEL);
  count_process = 0;
}

asmlinkage unsigned long * sys_get_syscall_list(void){
  
  return syscall_list;
}

asmlinkage void sys_set_allow(int bool){

  allow = bool;
}

asmlinkage int sys_get_allow(void){

  return allow;
}

asmlinkage int sys_get_count(void){
  return count_process;
}
