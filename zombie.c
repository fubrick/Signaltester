#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int i = 0;
	int numberOfZombies = 0;
	pid_t childPid, cleaned;

	if (argc != 3)
	{
		printf("Usage:zombie -n <number>\n");
		exit(EXIT_FAILURE);
	}
	else
		numberOfZombies = atoi(argv[2]);

	for (i = 0; i < numberOfZombies; ++i)
	{
		childPid = fork();
		if (childPid < 0) // error
		{
			printf("Error %d\n", childPid);
			exit(EXIT_FAILURE);
		}
		if (childPid == 0) // child
		{
			printf("Zombie %d, pid: %d\n", i,getpid());
			exit(EXIT_SUCCESS);  // turn into zombie
		}
	}
	sleep(1);
	printf("Press ENTER to kill zombies..\n");
	getchar();

	for (i = 0; i < numberOfZombies; ++i)
	{
		cleaned = wait(NULL);
		printf("zombie %d cleaned up\n", cleaned);
	}
	printf("Verify that zombies are gone.\nPress ENTER to end.\n");
	getchar();
	return 0;
}