#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid, rdbytes = 0, wrbytes = 0;
    char buf[512];
    const char prnt_message[] = "message from parent: ",
               cld_message[] = "message from child: ";
    struct flock prnt_rdlock, prnt_wrlock, cld_rdlock, cld_wrlock;

    pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        return 1;

    case 0:
        while (1)
        {
            cld_rdlock.l_type = F_RDLCK;
            cld_rdlock.l_whence = SEEK_CUR;
            cld_rdlock.l_start = 0;
            cld_rdlock.l_len = 0;

            cld_wrlock.l_type = F_WRLCK;
            cld_wrlock.l_whence = SEEK_CUR;
            cld_wrlock.l_start = 0;
            cld_wrlock.l_len = 0;

            while (fcntl(0, F_SETLKW, &cld_rdlock) == -1)
            {
            }

            while (fcntl(1, F_SETLKW, &cld_wrlock) == -1)
            {
            }

            rdbytes = read(0, buf, sizeof(buf));
            write(1, cld_message, sizeof(cld_message));
            write(1, buf, rdbytes);

            cld_rdlock.l_type = F_UNLCK;
            cld_wrlock.l_type = F_UNLCK;

            if (fcntl(0, F_SETLK, &cld_rdlock) == -1)
            {
            }
            if (fcntl(1, F_SETLKW, &cld_wrlock) == -1)
            {
            }
        }
        break;

    default:
        while (1)
        {
            prnt_rdlock.l_type = F_RDLCK;
            prnt_rdlock.l_whence = SEEK_CUR;
            prnt_rdlock.l_start = 0;
            prnt_rdlock.l_len = 0;

            prnt_wrlock.l_type = F_WRLCK;
            prnt_wrlock.l_whence = SEEK_CUR;
            prnt_wrlock.l_start = 0;
            prnt_wrlock.l_len = 0;

            while (fcntl(0, F_SETLK, &prnt_rdlock) == -1)
            {
            }

            while (fcntl(1, F_SETLK, &prnt_wrlock) == -1)
            {
            }

            rdbytes = read(0, buf, sizeof(buf));
            write(1, prnt_message, sizeof(prnt_message));
            write(1, buf, rdbytes);

            prnt_rdlock.l_type = F_UNLCK;
            prnt_wrlock.l_type = F_UNLCK;

            if (fcntl(0, F_SETLK, &prnt_rdlock) == -1)
            {
            }

            if (fcntl(1, F_SETLKW, &prnt_wrlock) == -1)
            {
            }
        }
        break;
    }

    return 0;
}