#include "msgbuf.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int msqid = -1;

void sig_handler(int sig)
{
    if ((msgctl(msqid, IPC_RMID, 0)) == -1)
    {
        perror("msgctl error");
    }
}

int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = sig_handler;
    sigaction(SIGINT, &act, 0);

    key_t key = ftok(__FILE__, 'A');
    if (key == -1)
    {
        perror("ftok error");
        return 1;
    }

    msqid = msgget(key, 0666 | IPC_CREAT);
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

        printf("message from client %ld to client %d: %s\n",
               buf.mtype, buf.receiver, buf.mtext);

        if ((msgsnd(buf.receiver, &buf, sizeof(buf.mtext), 0)) == -1)
        {
            perror("send error");
            return 4;
        }
    }

    return 0;
}