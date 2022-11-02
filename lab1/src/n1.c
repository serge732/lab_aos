#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main() 
{
    int fd;

    fd = open("n1_asset", O_RDONLY);

    printf("fd: %d\n", fd);
    printf("errno: %d\n", errno);
    printf("strerror(errno): %s\n", strerror(errno));
    perror("perror");

    return 0;
}