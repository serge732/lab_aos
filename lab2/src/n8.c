#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFSIZ 84

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid args!\nEnter %s <filename>\n", argv[0]);
        return -1;
    }

    int source_fid = open(argv[1], O_RDONLY);
    if (source_fid == -1)
    {
        perror("open perror");
        return -1;
    }

    int fork_result = fork();

    if (fork_result == 0)
    {
        int destination_fid = creat("n8_son_asset", 0644);

        char str_buf[BUFSIZ];
        read(source_fid, str_buf, BUFSIZ);

        write(destination_fid, str_buf, BUFSIZ);
        lseek(destination_fid, 0, SEEK_SET);
        read(destination_fid, str_buf, BUFSIZ);

        write(1, str_buf, BUFSIZ);
    }
    else
    {
        int destination_fid = creat("n8_father_asset", 0644);

        char str_buf[BUFSIZ];
        read(source_fid, str_buf, BUFSIZ);

        write(destination_fid, str_buf, BUFSIZ);
        lseek(destination_fid, 0, SEEK_SET);
        read(destination_fid, str_buf, BUFSIZ);

        wait(NULL);

        write(1, str_buf, BUFSIZ);
    }

    return 0;
}