#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct msqp
{
    long mtype;
    char mtext[1];
} msqp;

int main(int argc, char *argv[])
{
    int msqid;
    long mtype;

    if (argc != 3)
    {
        printf("Invalid args!"
               "Enter %s <msqid> <mtype>\n",
               argv[0]);
        return 1;
    }

    msqid = atoi(argv[1]);
    if (msqid == 0)
    {
        printf("Incorrect <msqid>\n");
        return 1;
    }

    mtype = strtol(argv[2], NULL, 0);
    if (mtype == 0)
    {
        printf("Incorrect <mtype>\n");
        return 1;
    }

    msqp buff;
    if ((msgrcv(msqid, &buff, sizeof(buff.mtext), mtype, IPC_NOWAIT | MSG_NOERROR)) == -1)
    {
        perror("msgrcv error");
        return 2;
    }

    printf("mtext: %s\n", buff.mtext);

    return 0;
}