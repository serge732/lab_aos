#include <stdio.h>
#include <unistd.h>

int main()
{
    int fp1[2], fp2[2];
    const char str1[] = "hello from parent";
    const char str2[] = "hello from child";
    char buf[255];

    if (pipe(fp1) != 0 || pipe(fp2) != 0)
    {
        return 1;
    }

    int pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        return 2;

    case 0:
        printf("i'm child\n");

        close(fp1[1]);
        close(fp2[0]);

        write(fp2[1], str2, sizeof(str2));
        read(fp1[0], buf, sizeof(buf));

        printf("parent said: %s\n", buf);

        close(fp1[0]);
        close(fp2[1]);

        break;

    default:
        printf("i'm parent\n");

        close(fp2[1]);
        close(fp1[0]);

        write(fp1[1], str1, sizeof(str1));
        read(fp2[0], buf, sizeof(buf));

        printf("child said: %s\n", buf);

        close(fp2[0]);
        close(fp1[1]);

        break;
    }

    return 0;
}