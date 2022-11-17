#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);

    int offset = lseek(fd, -1, SEEK_END);

    char ch;
    int bytes_read = read(fd, &ch, 1);

    while (offset > 0)
    {
        write(1, &ch, 1);
        offset = lseek(fd, -2, SEEK_CUR);
        bytes_read = read(fd, &ch, 1);
        offset += bytes_read;
    }

    write(1, "\n", 1);

    return 0;
}