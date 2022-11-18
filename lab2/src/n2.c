#include <stdio.h>
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
        printf("Son\n");
    }
    else
    {
        printf("Father\n");
    }
}