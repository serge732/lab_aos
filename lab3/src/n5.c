#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int pid = fork();
    if (pid == -1)
    {
        perror("fork error");
    }

    if (pid == 0)
    {
        printf("i'm child\n");

        int i = 0;
        while (i < 100)
        {
            printf("top level loop current value = %d\n", i);
            i++;

            int j = 0;
            while (j < 10000)
            {
                j++;

                int k = 0;
                while (k < 10000)
                {
                    k++;
                }
            }
        }
    }
    else
    {
        printf("i'm parent/ i want to kill my child...\n");
        kill(pid, SIGUSR1);

        int stat_loc;
        wait(&stat_loc);

        printf("i'm parent/ my child was completed with status %d\n", stat_loc);
    }

    return 0;
}