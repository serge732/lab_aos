#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define B_SZE 1

int copy(const int source_fd, const int destination_fd)
{
    char str_buffer[B_SZE];

    int bytes_read = read(source_fd, str_buffer, B_SZE);

    while (bytes_read > 0)
    {

        write(destination_fd, str_buffer, bytes_read);
        bytes_read = read(source_fd, str_buffer, B_SZE);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        return copy(0, 1);
    }
    else if (argc == 3)
    {
        int source_fd = open(argv[1], O_RDONLY);
        int destination_fd = open(argv[2], O_WRONLY);

        return copy(source_fd, destination_fd);
    }
}