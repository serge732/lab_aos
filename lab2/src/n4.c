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
        sleep(1);

        printf("--- SON ---\n");

        printf("Fork result: %d\n", fork_result);
        printf("PID: %d\nPPID: %d\nPGRP: %d\n\n",
               getpid(), getppid(), getpgrp());
    }
    else
    {
        printf("--- FATHER ---\n");

        printf("Fork result: %d\n", fork_result);
        printf("PID: %d\nPPID: %d\nPGRP: %d\n\n",
               getpid(), getppid(), getpgrp());
    }
}
