#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int bytes_read = 0;
    char buf[255];

    while ((bytes_read = read(STDIN_FILENO, buf, sizeof(buf))))
    {
        write(STDOUT_FILENO, buf, sizeof(buf));
        memset(buf, 0, sizeof(buf));
    }

    return 0;
}