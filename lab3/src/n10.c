#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int sig)
{
    printf("caught SIGINT\n");
    sleep(7);
}

void sig_usr1_handler(int sig)
{
    printf("caugth SIGUSR1\n");
    sleep(7);
}

int main()
{
    printf("pid = %d\n", getpid());
    fflush(stdout);

    struct sigaction intact, usr1act;

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);

    intact.sa_mask = set;
    intact.sa_handler = sig_handler;

    usr1act.sa_handler = sig_usr1_handler;

    sigaction(SIGINT, &intact, NULL);
    sigaction(SIGUSR1, &usr1act, NULL);

    while (1)
        pause();

    return 0;
}