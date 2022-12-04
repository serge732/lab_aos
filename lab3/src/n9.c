#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc > 2 || (argc == 2 && strcmp(argv[1], "1")))
    {
        printf("Invalid args!\n"
               "Enter %s <1> or without args\n",
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

        alarm(3);

        if (argc == 2 && !strcmp(argv[1], "1"))
        {
            void sig_handler(int sig)
            {
                printf("i'm child/"
                       "i caught signal %d\n",
                       sig);
            }

            signal(SIGALRM, sig_handler);
        }

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
        printf("i'm parent/"
               "i'm waiting for my child...\n");

        int stat_loc;
        wait(&stat_loc);

        printf("i'm parent/"
               "my child was completed with status %d\n",
               stat_loc);
    }

    return 0;
}