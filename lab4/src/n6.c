#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int rfd, bytes_read;
    char buf[15];

    if ((rfd = open(argv[1], O_RDONLY)) < 0)
    // if ((rfd = open("fifo_file", O_RDONLY | O_NDELAY)) < 0)
    {
        perror("open error");
        return 2;
    }

    while ((bytes_read = read(rfd, buf, sizeof(buf))) > 0)
        write(1, buf, bytes_read);

    close(rfd);

    return 0;
}