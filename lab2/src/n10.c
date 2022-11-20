#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
    if (argc != 2)
    {
        printf("Invalid args!\nEnter %s <path>\n", argv[0]);
        return -1;
    }

    pid_t fork_result = fork();

    if (fork_result == 0)
    {
        sleep(1);

        printf("--- SON --- \n");

        execl(argv[1], "l1", "l2", NULL);
    }
    else
    {
        printf("--- FATHER ---\n");

        printf("Args:\n");
        for (int i = 0; argv[i]; i++)
        {
            printf("%s\n", argv[i]);
        }

        printf("Environment:\n");
        for (int i = 0; envp[i]; i++)
        {
            printf("%s\n", envp[i]);
        }
    }

    return 0;
}