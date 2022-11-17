#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Invalid args!\n"
               "Expect at least one file");
        return -1;
    }

    int max_size = 0;
    char *max_filename;
    int current_size;

    for (int i = 1; i < argc; i++)
    {
        int fd = open(argv[i], O_RDONLY);
        current_size = lseek(fd, 0, SEEK_END);

        if (current_size > max_size)
        {
            max_size = current_size;
            max_filename = argv[i];
        }
    }

    printf("max size: %d\n"
           "file: %s\n",
           max_size, max_filename);

    return 0;
}