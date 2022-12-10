#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int fp[2], bytes_read = 0;
    char buf[255];

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
        break;

    case 0:
        close(fp[0]);

        while ((bytes_read = read(STDIN_FILENO, buf, sizeof(buf))))
        {
            write(fp[1], buf, sizeof(buf));
            memset(buf, 0, sizeof(buf));
        }

        close(fp[1]);
        break;

    default:
        close(fp[1]);

        do
        {
            bytes_read = read(fp[0], buf, sizeof(buf));
            printf("i'm parent. i have read from child: %s\n", buf);
        } while (bytes_read);

        close(fp[0]);
        break;
    }

    return 0;
}