#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fp[2], fp2[2], bytes_read = 0;
    char buf[255];

    if (pipe(fp) != 0 || pipe(fp2) != 0)
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
        close(fp2[1]);
        dup2(fp[1], STDOUT_FILENO);
        execl(argv[1], NULL);
        close(fp[1]);
        close(fp2[0]);
        break;

    default:
        close(fp[1]);
        close(fp2[0]);

        do
        {
            bytes_read = read(fp[0], buf, sizeof(buf));
            printf("i'm parent. i read it from %s: %s\n", argv[1], buf);
        } while (bytes_read);

        close(fp[0]);
        close(fp2[1]);
        break;
    }

    return 0;
}