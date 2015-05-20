#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t debugStatus = 0;

void sigint_handler(int signal)
{
	printf("\nsignal recieved: %d\n", signal);
	debugStatus = 1;
}


int main(int argc, char const *argv[])
{
	int i = 0;
	pid_t childPid[2];
	pid_t cleaned;

	signal(SIGINT, sigint_handler);

	for (i = 0; i < 2; ++i)
	{
	
		childPid[i] = fork();
		if (childPid[i] < 0) // error
		{
			printf("Error %d\n", childPid[i]);
			exit(EXIT_FAILURE);
		}

		if (childPid[i] == 0) // child
		{
			printf("Executing some binary from child %d, pid: %d\n", i,getpid());
			//wait for signal
			while(debugStatus == 0) {}
			//exit(EXIT_SUCCESS);
		}
	}

	//main process
	sleep(6);
	printf("waited 60 seconds..\n");

	for (i = 0; i < 2; ++i)
	{
		kill(childPid[i], SIGINT);
		cleaned = wait(NULL);
		printf("process %d cleaned up\n", cleaned);
	}
	return 0;
}