#include "types.h"
#include "user.h"
#include "globals.h"

int main(int argc, char *argv[])
{
	
	int exitWait(void);
	int waitPid(void);
	int PScheduler(void);
        int testInheritance(void);
	int testWaitTime(void);

  printf(1, "\n This program tests the correctness of your lab#1\n");
  
  if (atoi(argv[1]) == 1)
	exitWait();
  else if (atoi(argv[1]) == 2)
	waitPid();
  else if (atoi(argv[1]) == 3)
	PScheduler();
  else if (atoi(argv[1]) == 4)
        testInheritance();
  else if (atoi(argv[1]) == 5)
	testWaitTime();
  else 
   printf(1, "\ntype \"lab1 1\" to test exit and wait, \"lab1 2\" to test waitpid and \"lab1 3\" to test the priority scheduler \n");
  
    // End of test
	 exit(0);
 }
  
  
int exitWait(void) {
	  int pid, ret_pid, exit_status;
       int i;
  // use this part to test exit(int status) and wait(int* status)
 
  printf(1, "\n  Step 1: testing exit(int status) and wait(int* status):\n");

  for (i = 0; i < 2; i++) {
    pid = fork();
    if (pid == 0) { // only the child executed this code
      if (i == 0)
      {
      printf(1, "\nThis is child with PID# %d and I will exit with status %d\n", getpid(), 0);
      exit(0);
  }
      else
      {
	 printf(1, "\nThis is child with PID# %d and I will exit with status %d\n" ,getpid(), -1);
      exit(-1);
  } 
    } else if (pid > 0) { // only the parent exeecutes this code
      ret_pid = wait(&exit_status);
      printf(1, "\n This is the parent: child with PID# %d has exited with status %d\n", ret_pid, exit_status);
    } else  // something went wrong with fork system call
    {  
	  printf(2, "\nError using fork\n");
      exit(-1);
    }
  }
  return 0;
}

int waitPid(void){
	
  int ret_pid, exit_status;
  int i;
  int pid_a[5]={0, 0, 0, 0, 0};
 // use this part to test wait(int pid, int* status, int options)

 printf(1, "\n  Step 2: testing waitpid(int pid, int* status, int options):\n");

  for (i = 0; i <5; i++) {
    pid_a[i] = fork();
	
    if (pid_a[i] == 0) { // only the child executed this code
     
      
      printf(1, "\n The is child with PID# %d and I will exit with status %d\n", getpid(), 0);
      exit(0);}}
       
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[3]);
      ret_pid = waitpid(pid_a[3], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[1]);
      ret_pid = waitpid(pid_a[1], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[2]);
      ret_pid = waitpid(pid_a[2], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[0]);
      ret_pid = waitpid(pid_a[0], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[4]);
      ret_pid = waitpid(pid_a[4], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      
      return 0;
  }
      
      
     int PScheduler(void){
		 
    // use this part to test the priority scheduler. Assuming that the priorities range between range between 0 to 63
    // 0 is the highest priority. All processes have a default priority of 20 

  int pid, ret_pid, exit_status;
  int i,j,k;
  
    printf(1, "\n  Step 2: testing the priority scheduler and setpriority(int priority)) systema call:\n");
    printf(1, "\n  Step 2: Assuming that the priorities range between range between 0 to 63\n");
    printf(1, "\n  Step 2: 0 is the highest priority. All processes have a default priority of 20\n");
    printf(1, "\n  Step 2: The parent processes will switch to priority 0\n");
    setpriority(0);
    for (i = 0; i <  3; i++) {
	pid = fork();
	if (pid > 0 ) {
		continue;}
	else if ( pid == 0) {
//		printf(1, "\n Hello! this is child# %d and I will change my priority to %d \n",getpid(),60-20*i);
		setpriority(60-20*i);	
		for (j=0;j<50000;j++) {
			for(k=0;k<10000;k++) {
				asm("nop"); }}
		printf(1, "\n child# %d with priority %d has finished! \n",getpid(),60-20*i);		
		exit(0);
        }
        else {
			printf(2," \n Error \n");
			exit(-1);
        }
	}

	if(pid > 0) {
		for (i = 0; i <  3; i++) {
			ret_pid = wait(&exit_status);
                        // This print was commented out, but because ret_pid
                        // was not used, the file would not compile
			printf(1,"\n This is the parent: child with PID# %d has finished with status %d \n",ret_pid,exit_status);
			}
                     printf(1,"\n if processes with highest priority finished first then its correct \n");
}
			
	return 0;
}

int testInheritance() {

    int pid_block, pid_proc;
    int j, k;

    printf(1, "Testing priority inheritance\n");
    printf(1, "We create a process with low priority and a process with high priority.\n");
    printf(1, "The process with low priority blocks the process with high priority, so\n");
    printf(1, "low priority process inherits the high one\n\n");

    setpriority(0);

    // make low priority child
    pid_block = fork();
    
    // if it's the parent make the high priority child
    if (pid_block) { 
        pid_proc = fork();
    }

    if (pid_block == 0) { //low priority child
        setpriority(PRIORITY_LOW);
     
	for (j=0;j<50000;j++) {
	    for(k=0;k<10000;k++) {
		asm("nop");
            }
        }

        printf(1, "The high priority child donated its priority to me\n");
        exit(0);
    }

    if (pid_proc == 0) { //high priority child
        setpriority(20);
        printf(1, "I am the high priority child about to be proc blocked\n");
        setblocked(1);
        setprocblocked(pid_block);

	for (j=0;j<50000;j++) {
	    for(k=0;k<10000;k++) {
		asm("nop");
            }
        }
        
        printf(1, "If we've hit this, then the low priority child should have run already\n\n");
        exit(0);
    }

    waitpid(pid_block, 0, 0);
    waitpid(pid_proc, 0, 0);

    return 0;
}

int testWaitTime(void){
  int pid, ret_pid, exit_status;
  int i,j,k;
  
    printf(1, "\n  This is a test to track the turnaround time and wait time of each process.\n");
    printf(1, "\n  Each child process should exit and display their ID, wait time and turnaround time.\n");
   
    setpriority(0);
    for (i = 0; i <  3; i++) {
	pid = fork();
	if (pid > 0 ) {
		continue;}
	else if ( pid == 0) {
//		printf(1, "\n Hello! this is child# %d and I will change my priority to %d \n",getpid(),60-20*i);
		setpriority(60-20*i);	
		for (j=0;j<50000;j++) {
			for(k=0;k<10000;k++) {
				asm("nop"); }}
		printf(1, "\n child# %d with priority %d has finished! \n",getpid(),60-20*i);
		procTime();		
		exit(0);
        }
        else {
			printf(2," \n Error \n");
			exit(-1);
        }
	}

	if(pid > 0) {
		for (i = 0; i <  3; i++) {
			ret_pid = wait(&exit_status);
                        // This print was commented out, but because ret_pid
                        // was not used, the file would not compile
			printf(1,"\n This is the parent: child with PID# %d has finished with status %d \n",ret_pid,exit_status);
			}
                     printf(1,"\n If all child processes display their turnaround time and wait time then the test is a success. \n");
}
			
	return 0;
}

