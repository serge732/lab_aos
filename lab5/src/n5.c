#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char *argv[])
{
    int msqid;

    if (argc != 2)
    {
        printf("Invalid args!"
               "Enter %s <msqid>\n",
               argv[0]);
        return 1;
    }

    msqid = atoi(argv[1]);
    if (msqid == 0)
    {
        printf("Incorrect <msqid>\n");
        return 1;
    }

    if ((msgctl(msqid, IPC_RMID, 0)) == -1)
    {
        perror("msgctl error");
        return 2;
    }

    return 0;
}