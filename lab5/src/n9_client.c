#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int server_msqid, client_msqid;
    long mtype;

    if (argc != 4)
    {
        printf("Invalid args!\n"
               "Enter %s <server_msqid> <client_msqid> <mtype>\n",
               argv[0]);
        return 1;
    }

    server_msqid = atoi(argv[1]);
    if (server_msqid == 0)
    {
        printf("Incorrect <server_msqid>\n");
        return 1;
    }

    client_msqid = atoi(argv[2]);
    if (client_msqid == 0)
    {
        printf("Incorrect <client_msqid>\n");
        return 1;
    }

    mtype = strtol(argv[3], NULL, 0);
    if (mtype == 0)
    {
        printf("Incorrect <mtype>\n");
        return 1;
    }

    printf("client %ld started...\n", mtype);

    while (1)
    {
        struct server_msg received_msg;
        received_msg.mtype = mtype;
        long receiver_mtype;
        char message[256];

        printf("Enter receiver mtype: \n");
        scanf("%ld", &receiver_mtype);

        if (receiver_mtype == 0)
        {
            printf("Incorrect <receiver_mtype>\n");
            return 2;
        }

        printf("Enter message: \n");
        scanf("%s", message);

        if ((send(server_msqid, mtype, receiver_mtype, message)) == -1)
        {
            perror("send error");
            return 3;
        }

        printf("waiting message with mtype %ld...\n", mtype);

        if ((msgrcv(client_msqid, &received_msg, sizeof(received_msg.mtext), mtype, 0)) == -1)
        {
            perror("msgrcv error");
            return 4;
        }

        printf("message from client %d with mtype %ld: %s\n",
               received_msg.sender_msqid, received_msg.mtype, received_msg.mtext);
    }

    return 0;
}