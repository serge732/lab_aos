#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_handler(int signo)
{
    printf("Получен сигнал %d\n", signo);
    signal(signo, SIG_DFL);
    /* Разве для signal после получаения сигнала его диспозиция
    не должна устанавливаться на значение по умолчанию? */
}

int main()
{
    signal(SIGINT, sig_handler);
    while (1)
        pause();

    return 0;
}