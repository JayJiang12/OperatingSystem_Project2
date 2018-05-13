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

void set_list(){
  syscall(_set_syscall_list);
}

long * get_list(){
  syscall(_get_syscall_list);
}

long get_count(){
  syscall( _get_count);
}

int compareList(char *fList, char*sList);

int main(){

  long process_id;
  long allow;
  int exit = 1;
  long * list1;
  long * list2;
  int list_number = 0;
  long count1 = 0;
  long count2 = 0;
  
  printf("Please enter ps aux to get PID before of program\n");
  
  while(exit){
    
    printf("Please enter PID: ");
    scanf("%ld", &process_id);

    set_PID(process_id);

    printf("enter 1 to start log syscall number: ");
    scanf("%ld", &allow);
    set_allow(allow);

    set_list();
    
    printf("list start recording syscall number...\n");

    printf("enter 0 to stop recording: ");
    scanf("%ld", &allow);
    set_allow(allow);

    if(list_number = 1){
      list1 = get_list();
      count1 = get_count();
      printf("Number of Syscall: %ld\n", count1);
    }
    else if(list_number = 2){
      list2 = get_list();
      count2 = get_count();
      printf("Number of Syscall: %ld\n", count2);
    }
    else{
      printf("already record two list\n");
      break;
    }
    list_number++;
     if(list_number == 2) {
      printf("already record two list\n");
      exit = 0;
    }
  }

  

  
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
