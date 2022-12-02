#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_handler(int signo)
{
    printf("Получен сигнал %d\n", signo);
}

int main()
{
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_handler = sig_handler;
    act.sa_flags = SA_RESETHAND;

    sigaction(SIGINT, &act, 0);

    while (1)
        pause();

    return 0;
}