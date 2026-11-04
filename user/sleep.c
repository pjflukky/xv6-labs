#include "kernel/types.h"
#include "kernel/stat.h" 
#include "user/user.h"

 /* Notes: main(argc, char* argv[]) main can be passed with arguments and must be in this order!!
  * => you should look at user.h for system_calls or user functions that is available for use
  */

/*
 * sleep.c halt a function for a certain ticks
 */
int main(int argc, char* argv[]){
  // check valid 
  if(argc != 2){
    fprintf(2, "Invalid; Usage: sleep ticks\n"); 
    exit(1);
  }
  int ticks = atoi(argv[1]);   
  if(pause(ticks) < 0){
    fprintf(2, "sleep error");
  }


  exit(0);
}
