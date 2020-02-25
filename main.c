#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>

void printProcessInformation();
void logic();
//gets new variables after executing a new process
int main(void)
{
	logic();
}


void logic()
{
	long time_start, time_end;
	int status;
	struct tms t;
	clock_t clk;
	//start of the program 
	time_start = time(NULL); 
	printf("START: %li\n", time_start);
	//spawn a process
	pid_t pid = fork();
	//we are the child process, print information
	if((int)pid == 0)
	{
		printProcessInformation((int)pid, status);
		exit(0);
	}

	//check for error in times()
 	if ((clk = times(&t)) == -1)
    	perror("times() error");
	//we are the parent process so wait for the child
	else if((int)(pid) > 0)
	{	
		waitpid(pid, &status, 0);
		printProcessInformation((int)pid, status);
		printf("USER: %f, SYS: %f \n", (double)t.tms_utime, (double)t.tms_stime);
		printf("CUSER: %f, CSYS: %f \n", (double)t.tms_cutime, (double)t.tms_cstime);
	}
	//print process time user, system, user time of children, and system time of children.
	time_end = time(NULL); 
	printf("STOP: %li\n", time_end);
}


void printProcessInformation(int pid, int status)
{
	//succesful exit 
	if (pid != 0 && WIFEXITED(status))
	{
		int returned = WEXITSTATUS(status);
		printf("PPID: %d, PID: %d, CPID: %d, RETVAL: %d \n", getppid(), getpid(), pid, returned);
	}
	else{
		printf("PPID: %d, PID: %d \n", getppid(), getpid());
	}
}