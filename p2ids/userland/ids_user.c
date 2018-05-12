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
#include<string.h>
#include<unistd.h>

#define _set_PID 333
#define _get_PID 334
#define _set_syscall_list 335
#define _get_syscall_list 336
#define _set_allow 337
#define _get_allow 338
#define _get_count 339

void set_PID(long PID){
  syscall(_set_PID, PID);
}

long get_PID(){
  return syscall(_get_PID);
}

void set_allow(long allow){
  syscall(_set_allow, 1);
}

long get_allow(){
  syscall(_get_allow);
}


int compareList(char *fList, char*sList);

int main(){

  long process_id;

  printf("if need, use ps or ps aux to get PID\n");
  printf("Please enter PID: ");
  scanf("%ld", &process_id);
   
  //  syscall(_set_syscall_list);
  syscall(_set_allow, 1);
  set_PID(process_id);

   printf("%ld\n", get_PID());
   printf("allow: %d\n", get_allow());
}

int compareInt(unsigned long * fList, unsigned long *sList, int k){

  int i;
  int error = 0;
  int size;// = syscall(_get_count());
  int position = size - 1;
  
  for(i = 0; i < k; i++){ 
    if (fList[position] !=  sList[position]){
      error++;
    }
  }

  position--;
  
}
