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

int get_allow(){
  syscall(_get_allow);
}

void set_list(){
  syscall(_set_syscall_list);
}

long * get_list(){
  syscall(_get_syscall_list);
}

int get_count(){
  syscall( _get_count);
}

int compareInt(long *fList, long * sList, int k, int size1, int size2);

int main(){

  long process_id;
  int allow;
  int exit = 1;
  long * list1;
  long * list2;
  int list_number = 1;
  int count1 = 0;
  int count2 = 0;
  int k;
  int result;
  
  printf("Please enter ps aux to get PID before of program\n");
  
  while(exit){
    
    printf("Please enter PID: ");
    scanf("%ld", &process_id);

    set_PID(process_id);

    printf("enter 1 to start record syscall number: ");
    scanf("%i", &allow);
    set_allow(allow);

    set_list();
    
    printf("list start recording syscall number...\n");

    printf("enter 0 to stop recording: ");
    scanf("%i", &allow);
    set_allow(allow);

    if(list_number == 1){
      list1 = get_list();
      count1 = get_count();
      printf("Number of Syscall in list: %i\n", count1);
    }
    else if(list_number == 2){
      list2 = get_list();
      count2 = get_count();
      printf("Number of Syscall in list: %i\n", count2);
    }
  
    list_number++;

    if(list_number > 2) {
      printf("already record two list\n");
      exit = 0;
    }
  }

  printf("Please enter how many syscall you want to compare: ");
  scanf("%i", &k);
  
  result = compareInt(list1, list2, 0, count1, count2);

  if(result == 0){
    printf("program is attacked\n");
  }
  else if(result == 1){
    printf("program is safe\n");
  }
  else{
    printf("Error! Please check your compare function\n");
  }
  
}

int compareInt(long * fList, long *sList, int k, int size1, int size2){

  int i;
  int error = 0;
  int position1 = size1 - 1;
  int position2 = size2 - 1;
  int persent = 10; // number of persent to be consider as being attacked
  
  for(i = 0; i < k; i++){ 
    if (fList[position1] !=  sList[position2]){
      error++;
    }
    position1--;
    position2--;
  }

  if(error <= (k / persent)){
    return 1;
  }
  else{
    return 0;
  }
  
}
