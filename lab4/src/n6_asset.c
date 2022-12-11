#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int wfd;
    const char buf[] = "hello!\n";

    if ((wfd = open(argv[1], O_WRONLY | O_NDELAY)) < 0)
    {
        perror("open error");
        return 2;
    }

    write(wfd, buf, sizeof(buf));

    close(wfd);

    return 0;
}