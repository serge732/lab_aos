#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFSZ 3

void sig_handler(int sig)
{
    printf("caugth %d\n", sig);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid args!\n"
               "Enter %s <filename>\n",
               argv[0]);
        return 1;
    }

    struct sigaction act;
    sigset_t mask;
    char cld_buf[BUFSZ];
    char prnt_buf[BUFSZ];
    int bytes_read_cld = 0;
    int bytes_read_prnt = 0;

    act.sa_handler = sig_handler;
    sigemptyset(&act.sa_mask);
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);

    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("open error");
        return 2;
    }

    int pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        return 3;

    case 0:
        sigdelset(&mask, SIGUSR2);

        bytes_read_cld = read(fd, cld_buf, BUFSZ);
        if (bytes_read_cld == -1)
        {
            perror("read error");
            return 4;
        }

        while (bytes_read_cld)
        {
            write(STDOUT_FILENO, cld_buf, BUFSZ);
            kill(getppid(), SIGUSR1);
            sigsuspend(&mask);
            bytes_read_cld = read(fd, cld_buf, BUFSZ);
            if (bytes_read_cld == -1)
            {
                perror("read error");
                return 4;
            }
        }

        break;

    default:
        sigdelset(&mask, SIGUSR1);
        sigsuspend(&mask);

        bytes_read_prnt = read(fd, prnt_buf, BUFSZ);
        if (bytes_read_prnt == -1)
        {
            perror("read error");
            return 4;
        }

        while (bytes_read_prnt)
        {
            write(STDOUT_FILENO, prnt_buf, BUFSZ);
            kill(pid, SIGUSR2);
            sigsuspend(&mask);
            bytes_read_prnt = read(fd, prnt_buf, BUFSZ);
            if (bytes_read_prnt == -1)
            {
                perror("read error");
                return 4;
            }
        }

        break;
    }

    return 0;
}