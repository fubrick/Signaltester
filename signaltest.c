#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t debugStatus = 0;

void sigint_handler(int signal)
{
	//printf("kernal signal number: %d\n", signal);
	if (debugStatus == 0)
		debugStatus = 1;
	else
		debugStatus = 0;
}

void user_handler(int signal)
{
	printf("\nsignal recieved from kernal: %d\n", signal);
	exit(EXIT_SUCCESS);
}

int main(void)
{
	int i = 0, pause = 2;
	printf("process id is: %d\n", getpid());
	signal(SIGINT, sigint_handler);
	signal(SIGUSR1, user_handler);

	while (1 == 1)
	{
		//printf("Sleeping for 2 seconds...\n");
		sleep(pause);

		i++;
		if ( debugStatus == 1)
			printf("\nIterations: %d\n", i);
	}
}
