#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define B_SZE 1

int copy()
{
    char str_buffer[B_SZE];

    int bytes_read = read(0, str_buffer, B_SZE);

    while (bytes_read > 0)
    {

        write(1, str_buffer, bytes_read);
        bytes_read = read(0, str_buffer, B_SZE);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        copy();
    }
    else if (argc == 3)
    {
        close(0);
        open(argv[1], O_RDONLY);

        close(1);
        open(argv[2], O_WRONLY);

        copy();
    }
    else
    {
        printf("Invalid args!"
               "Enter %s <source filename> <destination filename> "
               "or call without args!",
               argv[0]);
    }

    return 0;
}