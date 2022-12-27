#include "msgbuf.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int server_msqid = -1;
int client_msqid = -1;

void sig_handler(int sig)
{
    if ((msgctl(server_msqid, IPC_RMID, 0)) == -1)
    {
        perror("server msgctl error");
    }
    if ((msgctl(client_msqid, IPC_RMID, 0)) == -1)
    {
        perror("client msgctl error");
    }
}

int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = sig_handler;
    sigaction(SIGINT, &act, 0);

    key_t server_key = ftok(__FILE__, 'A');
    if (server_key == -1)
    {
        perror("server ftok error");
        return 1;
    }

    key_t client_key = ftok(__FILE__, 'B');
    if (client_key == -1)
    {
        perror("client ftok error");
        return 1;
    }

    server_msqid = msgget(server_key, 0666 | IPC_CREAT);
    if (server_msqid == -1)
    {
        perror("server msgget error");
        return 2;
    }

    client_msqid = msgget(client_key, 0666 | IPC_CREAT);
    if (client_msqid == -1)
    {
        perror("client msgget error");
        return 2;
    }

    printf("server %d started...\n", server_msqid);
    printf("client %d started...\n", client_msqid);

    while (1)
    {
        struct msgbuf buf;

        if ((msgrcv(server_msqid, &buf, sizeof(buf.mtext), 0, 0)) == -1)
        {
            perror("msgrcv error");
            return 3;
        }

        printf("message from client %ld to client %d: %s\n",
               buf.mtype, buf.receiver, buf.mtext);

        buf.mtype = buf.receiver;

        if ((msgsnd(client_msqid, &buf, sizeof(buf.mtext), 0)) == -1)
        {
            perror("send error");
            return 4;
        }
    }

    return 0;
}