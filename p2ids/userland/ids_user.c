/**
 ** file: ids_user.c
 ** CMSC441 
 ** Project 2
 **
 ** IDS system
 **/

#include<stdio.h>
#include<unistd.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<stirng.h>
#include<unistd.h>

#define _set_PID 333
#define _get_PID 334
#define _set_syscall_list 335
#define _get_syscall_list 336
#define _set_allow 337
#define _get_allow 338
#define _get_count 339

void run();
int compareList(char *fList, char*sList);

void run(){

  pid_t pid = fork();

  int current_PID = int(getpid());
  // int current_PID = "001";
  
  // kernel system call
  syscall(_set_syscall_list());
  syscall(_set_PID(current_PID));
  syscall(_set_allow(1));
}

int compareStr(char * fList, char *sList){

  int i;
  int fsize = sizeof(flist)/sizeof(fList[0]);
  int sSzie = sizeof(sList)/sizeof(sList[0]);
  int error;

  while(fList != '\0' || sList != '\0'){

    if (strcmp(fList[i], sList[i]) != 0){
      error++;
    }

    i++;
  }
}

int compareInt(char * fList, char *sList){

  int i = 0;
  int error = 0;
  
  while(fList != '\0' || sList != '\0'){

    if (fList[i] !=  sList[i]){
      error++;
    }

    i++;
  }
}
