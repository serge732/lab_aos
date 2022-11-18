#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	printf("Calling fork...\n\n");

	int fork_result = fork();
	if (fork_result == -1)
	{
		perror("fork error");
	}

	if (fork_result == 0)
	{
		printf("--- SON ---\n");

		printf("Fork result: %d\n", fork_result);
		printf("PID: %d\nPPID: %d\nPGRP: %d\n\n",
			   getpid(), getppid(), getpgrp());
	}
	else
	{
		int stat_loc;

		int pid = wait(&stat_loc);

		printf("--- FATHER ---\n");
		printf("Proc %d complete!\nstat_loc: %d\n",
			   pid, stat_loc);

		printf("Fork result: %d\n", fork_result);
		printf("PID: %d\nPPID: %d\nPGRP: %d\n\n",
			   getpid(), getppid(), getpgrp());
	}
}
