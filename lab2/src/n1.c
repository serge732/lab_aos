#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Invalid args!\n"
               "Enter %s <name> <value>",
               argv[0]);
        return -1;
    }

    int setenv_result = setenv(argv[1], argv[2], 0);
    if (setenv_result != 0)
    {
        perror("setenv perror");
        return -1;
    }

    printf("Set env complete!\n");

    return 0;
}