#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pid, rdfd, wrfd, rdbytes = 0, wrbytes = 0;
    char rdbuf[3];
    const char wrmessage[] = "00\n";
    int writerator = 0;

    pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        return 1;

    case 0:
        close(rdfd);
        wrfd = open(argv[1], O_WRONLY);
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
        rdfd = open(argv[1], O_RDONLY);
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