#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pid, rdfd, wrfd, rdbytes = 0, wrbytes = 0;
    char rdbuf[3];
    struct flock rdlock, wrlock;
    const char wrmessage[] = "00";
    int writerator = 0;

    pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        return 1;

    case 0:
        wrlock.l_type = F_WRLCK;
        wrlock.l_whence = SEEK_SET;
        wrlock.l_start = 0;
        wrlock.l_len = 0;
        wrfd = open(argv[1], O_WRONLY);
        if (fcntl(wrfd, F_SETLK, &wrlock) < 0)
        {
            perror("wrlock error");
            return 3;
        }
        while ((writerator++ < 89))
        {
            wrbytes = write(wrfd, wrmessage, sizeof(wrmessage));
            if (wrbytes == -1)
            {
                perror("write error");
                return 3;
            }
        }
        close(wrfd);
        break;

    default:
        rdlock.l_type = F_RDLCK;
        rdlock.l_whence = SEEK_SET;
        rdlock.l_start = 0;
        rdlock.l_len = 0;
        rdfd = open(argv[1], O_RDONLY);
        if (fcntl(rdfd, F_SETLK, &rdlock) < 0)
        {
            perror("rdlock error");
            return 3;
        }
        while ((rdbytes = read(rdfd, rdbuf, sizeof(rdbuf))) > 0)
        {
            if (rdbytes == -1)
            {
                perror("read error");
                return 2;
            }
            printf("read from file: %s", rdbuf);
        }
        break;
    }

    return 0;
}