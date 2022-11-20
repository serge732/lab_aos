#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Invalid args!\nEnter %s <command>\n", argv[0]);
        return -1;
    }

    pid_t fork_result = fork();

    if (fork_result == 0)
    {
        printf("--- EXECVP ---\n");

        char **new_argv = argv + 1;
        execvp(argv[1], new_argv);
    }
    else
    {
        wait(NULL);

        printf("--- SYSTEM ---\n");

        system(argv[1]);
    }
}