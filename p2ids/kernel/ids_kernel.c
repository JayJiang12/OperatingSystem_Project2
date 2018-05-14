#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/proc_fs.h>
#include<linux/slab.h>
#include<linux/string.h>
#include<asm/uaccess.h>
#include<linux/mm.h>
#include<linux/fcntl.h>

asmlinkage void sys_set_PID(long PID);
asmlinkage long sys_get_PID(void);
asmlinkage void sys_set_syscall_list(void);
asmlinkage long * sys_get_syscall_list(void);
asmlinkage void sys_set_allow(int bool);
asmlinkage int sys_get_allow(void);
asmlinkage int sys_get_count_process(void);

asmlinkage void init_read(void);
asmlinkage int init_write(void);

void file_read(const char * filename);
void file_write(char * filename, char * data);

long processID;
long * syscall_list[1000000];
char * list;
int allow;
int count_process;


asmlinkage void sys_set_PID(long PID){

  processID = PID;
  
}

asmlinkage long sys_get_PID(void){
  return processID;
}

asmlinkage void sys_set_syscall_list(void){

  count_process = 0;
}

asmlinkage long * sys_get_syscall_list(void){
  int i;
  printk("Print first number syscall number\n");
  for(i = 0; i < 100; i++)
    printk("syscall number: %d", syscall_list[i]);
  return (long *)syscall_list;
}

asmlinkage void sys_set_allow(int bool){

  allow = bool;
}

asmlinkage int sys_get_allow(void){

  return allow;
}

asmlinkage int sys_get_count_process(void){
  return count_process;
}

asmlinkage int sys_init_write(void){
  char * filename="project2";

  file_write(filename, list);
  return 0;
}

asmlinkage void sys_init_read(void){
  char * filename="project2";

  file_read(filename);
}
void file_write(char * filename, char * data){
  struct file *filp;

  mm_segment_t fs;
  filp = filp_open(filename, O_RDWR|O_APPEND, 0064);

  if(IS_ERR(filp)){
    printk("open file error!\n");
      return;
  }

  fs = get_fs();
  set_fs(KERNEL_DS);
  filp->f_op->write(filp, data, strlen(data), &filp->f_pos);
  set_fs(fs);
  filp_close(filp, NULL);
}

void file_read(const char *filename){
  int fd;
  char buf[1];

  mm_segment_t old_fs = get_fs();
  set_fs(KERNEL_DS);

  fd = sys_open(filename, O_RDONLY, 0);
  if(fd>= 0){
    printk(KERN_DEBUG);
    while(sys_read(fd, buf, 1) == 1)
      printk("%c", buf[0]);
    printk("\n");
    sys_close(fd);
  }
  set_fs(old_fs);
}
  
