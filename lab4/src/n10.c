#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid, rdbytes = 0, wrbytes = 0;
    char buf[512];
    const char prnt_message[] = "message from parent: ",
               cld_message[] = "message from child: ";

    pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        return 1;

    case 0:
        while (1)
        {
            rdbytes = read(0, buf, sizeof(buf));
            write(1, cld_message, sizeof(cld_message));
            write(1, buf, rdbytes);
        }
        break;

    default:
        while (1)
        {
            rdbytes = read(0, buf, sizeof(buf));
            write(1, prnt_message, sizeof(prnt_message));
            write(1, buf, rdbytes);
        }
        break;
    }

    return 0;
}