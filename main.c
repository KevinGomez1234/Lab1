#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

//gets new variables after executing a new process
int main(int argc, char * argv[])
{
	long time_start, time_end;
	int stat_loc;
	//start of the program 
	time_start = time(NULL); 
	printf("START PARENT: %li\n", time_start);

	//spawn a process
	pid_t pid = fork();
	//we are the child print 
	if((int)pid == 0)
	{
		printf("This is the child\n");
	}

	//we are the parent process so wait for the child
	else if((int)(pid) > 0)
	{	
		waitpid(pid, &stat_loc, 0);
		sleep(10);
		time_end = time(NULL);
		printf("End Parent: %li\n", time_end);
	}

	if(WEXITSTATUS(stat_loc))
	{
		printf("Success\n");
	}
	else if(WIFSIGNALED(stat_loc))
	{
		printf("error\n");
	}
	else{
		printf("whattafuk\n");
	}
}


void printProcessInformation()
{
	printf("PPID: %d PID: %d \n", getppid(), getpid());
}