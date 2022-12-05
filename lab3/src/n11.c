#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
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

    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGINT);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    struct sigaction usr1act, usr2act;

    usr1act.sa_handler = sig_handler;
    sigaction(SIGUSR1, &usr1act, NULL);

    usr2act.sa_handler = sig_handler;
    sigaction(SIGUSR2, &usr2act, NULL);

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
        sigset_t cldmask;
        sigprocmask(SIG_SETMASK, NULL, &cldmask);
        sigdelset(&cldmask, SIGUSR2);

        char cld_buf[BUFSZ];
        int bytes_read_cld = read(fd, cld_buf, BUFSZ);
        if (bytes_read_cld == -1)
        {
            perror("read error");
            return 4;
        }

        while (bytes_read_cld)
        {
            printf("%s\n", cld_buf);
            kill(getppid(), SIGUSR1);
            sigsuspend(&cldmask);
            sleep(1);
            bytes_read_cld = read(fd, cld_buf, BUFSZ);
        }

        break;

    default:
        sigset_t prntmask;
        sigprocmask(SIG_SETMASK, NULL, &prntmask);
        sigdelset(&prntmask, SIGUSR1);
        sigsuspend(&prntmask);

        char prnt_buf[BUFSZ];
        int bytes_read_prnt = read(fd, prnt_buf, BUFSZ);
        if (bytes_read_prnt == -1)
        {
            perror("read error");
            return 4;
        }

        while (bytes_read_prnt)
        {
            printf("%s\n", prnt_buf);
            kill(pid, SIGUSR2);
            sigsuspend(&prntmask);
            sleep(1);
            bytes_read_prnt = read(fd, prnt_buf, BUFSZ);
        }

        break;
    }

    return 0;
}