#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    setbuf(stdout, NULL);

    struct sigaction act;
    act.sa_flags = SA_NOCLDWAIT;
    sigaction(SIGCHLD, &act, 0);

    int pid = fork();
    if (pid == 0)
    {
        printf("i'm child c:\n");
    }
    else
    {
        printf("i'm parent. My child pid = %d\n", pid);
        pause();
    }

    return 0;
}