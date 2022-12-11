#include <stdio.h>
#include <unistd.h>

int main()
{
    int fp[2];

    if (pipe(fp) != 0)
    {
        perror("pipe error");
        return 1;
    }

    int pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        return 2;

    case 0:
        close(fp[1]);
        dup2(fp[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
        break;

    default:
        close(fp[0]);
        dup2(fp[1], STDOUT_FILENO);
        execlp("who", "who", NULL);
        break;
    }

    return 0;
}