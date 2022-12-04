#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Invalid args!\n"
               "Enter %s <sig> or without args\n",
               argv[0]);
        return 1;
    }

    int pid = fork();
    if (pid == -1)
    {
        perror("fork error");
    }

    if (pid == 0)
    {
        printf("i'm child\n");
        pause();
    }
    else
    {
        printf("i'm parent/"
               "i want to kill my child...\n");
        sleep(1);

        int sig = 0;
        if (argc == 2)
        {
            sig = atoi(argv[1]);
        }

        if (sig == 0)
        {
            sig = SIGUSR1;
        }

        kill(pid, sig);

        int stat_loc;
        wait(&stat_loc);

        printf("i'm parent/"
               "my child was completed with status %d\n",
               stat_loc);
    }

    return 0;
}