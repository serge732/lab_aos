#include "msgbuf.h"
#include <errno.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char *argv[])
{
    key_t key = ftok(__FILE__, 'A');
    if (key == -1)
    {
        perror("ftok error");
        return 1;
    }

    int msqid = msgget(key, 0666 | IPC_CREAT);
    if (msqid == -1)
    {
        perror("msgget error");
        return 2;
    }

    printf("server %d started...\n", msqid);

    while (1)
    {
        struct msgbuf buf;

        if ((msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0)) == -1)
        {
            perror("msgrcv error");
            return 3;
        }

        printf("message from client %d to server: %s\n",
               buf.receiver, buf.mtext);

        if ((msgsnd(buf.receiver, &buf, sizeof(buf.mtext), 0)) == -1)
        {
            perror("send error");
            return 4;
        }

        printf("server answered to %d\n\n", buf.receiver);
    }

    return 0;
}