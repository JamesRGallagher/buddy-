#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buddy.h"


#define memory 4096 //we are using 4k of memory

struct block blockArr[memory]; //array of blocks
int position = 0;


void allocate(request){
  if(request>memory){
    printf("Your request is bigger than the total memory!\n");
    return;
  } else {

     

  }
}

void getInput(){
  char command[1];
  int value;
  printf("Input Command: ");
  scanf("%s %d", command,&value);
  if(strncmp(command,"A",1)==0){
    printf("we are allocating %d\n",value);
    allocate(value);
  } else if (strncmp(command,"F",1)==0){
    printf("we are freeing %d \n",value);
  } else{
    printf("invalid command\n");
  }
}


int main()
{
  //initialise the first blocx
  struct block first = { .size = memory, .position = 0, .flag = 0. };
  blockArr[position] = first;
  getInput();
   return(0);
}
