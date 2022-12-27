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

    printf("server %d started ...\n", msqid);

    while (1)
    {
        struct msgbuf buf;
        buf.mtype = 7707;

        if ((msgrcv(msqid, &buf, sizeof(buf.mtext), 7707, 0)) == -1)
        {
            perror("msgrcv error");
            return 3;
        }

        printf("received message with mtype %ld to client %d: %s\n",
               buf.mtype, buf.receiver, buf.mtext);

        buf.mtype = buf.receiver;

        if ((msgsnd(msqid, &buf, sizeof(buf.mtext), 0)) == -1)
        {
            perror("msgsnd error");
            return 4;
        }
    }

    return 0;
}