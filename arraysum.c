//Using pipes, find the sum of an array as follows - 
//One process calculates the sum of half the array and stores it in the pipe 
//The second process calculates the sum of the other half of the array, 
//reads the sum on the pipe and returns the total sum 

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
   int pipefds[2];
   int returnstatus;
   int pid;
   int array[]={10,22,35,74,45};
   int readsum;
   returnstatus = pipe(pipefds);
   if (returnstatus == -1) {
      printf("Unable to create pipe\n");
      return 1;
   }
   pid = fork();

   // child process
   if (pid != 0) {
      int n = sizeof(array)/sizeof(array[0]);
      int hsum = 0;
      for(int i = 0; i < n/2; i++){
         hsum += array[i];
      }
	   printf("Child Process - Writing half array sum to pipe\n");
      write(pipefds[1], &hsum, sizeof(hsum));
      
   } else { //parent process
      wait(NULL);
      read(pipefds[0], &readsum, sizeof(readsum));
      printf("Parent Process - Reading from pipe\n");
      int n = sizeof(array)/sizeof(array[0]);
      int hsum = 0;
      for(int i = n/2; i < n; i++){
         hsum += array[i];
      }
      int sum = hsum + readsum;
      printf("Total sum of array = %d\n", sum);
   }
   return 0;
}