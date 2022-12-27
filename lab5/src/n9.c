#include "server.h"
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

int main(int argc, char *argv[0])
{
    struct sigaction act;
    act.sa_handler = sig_handler;
    sigaction(SIGINT, &act, 0);

    key_t server_key = ftok(argv[0], 7);
    if (server_key == -1)
    {
        perror("server ftok error");
        return 1;
    }

    key_t client_key = ftok(argv[0], 11);
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

    printf("server %d started...\n"
           "answers will be sending to %d\n",
           server_msqid, client_msqid);

    while (1)
    {
        struct server_msg received_msg;

        if ((msgrcv(server_msqid, &received_msg, sizeof(received_msg.mtext), 0, IPC_NOWAIT)) == -1)
        {
            if (errno == ENOMSG)
            {
                continue;
            }

            perror("msgrcv error");
            return 3;
        }

        printf("message from client %d to client %ld: %s\n",
               received_msg.sender_msqid, received_msg.mtype, received_msg.mtext);

        if ((send(client_msqid, received_msg.sender_msqid, received_msg.mtype, received_msg.mtext)) == -1)
        {
            perror("send error");
            return 4;
        }
    }

    return 0;
}