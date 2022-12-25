#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int server_msqid;

    if (argc != 2)
    {
        printf("Invalid args!\n"
               "Enter %s <server_msqid>\n",
               argv[0]);
        return 1;
    }

    server_msqid = atoi(argv[1]);
    if (server_msqid == 0)
    {
        printf("Incorrect <server_msqid>\n");
        return 1;
    }

    int msqid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if (msqid == -1)
    {
        perror("msgget error");
        return 2;
    }

    printf("client %d started...\n", msqid);

    while (1)
    {
        struct server_msg received_msg;
        int client_msqid;
        char message[256];

        printf("Enter client msqid: \n");
        scanf("%d", &client_msqid);

        if (client_msqid == 0)
        {
            printf("Incorrect <client_msqid>\n");
            return 1;
        }

        printf("Enter message: \n");
        scanf("%s", message);

        if ((send(server_msqid, msqid, client_msqid, message)) == -1)
        {
            perror("send error");
            return 3;
        }

        if ((msgrcv(msqid, &received_msg, sizeof(received_msg.mtext), 0, 0)) == -1)
        {
            perror("msgrcv error");
            return 4;
        }

        printf("message from client %ld: %s\n", received_msg.mtype, received_msg.mtext);
    }

    return 0;
}