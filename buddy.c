#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int id;
	if (argc > 1)
	{
		id = atoi(argv[1]);
		printf("signaling pid: %d\n", id);
		kill(id, SIGUSR1);
	}
}
