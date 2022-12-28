#include "msgbuf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int server_msqid, client_msqid;

    if (argc != 3)
    {
        printf("Invalid args!\n"
               "Enter %s <server_msqid> <client_msqid>\n",
               argv[0]);
        return 1;
    }

    server_msqid = atoi(argv[1]);
    if (server_msqid == 0)
    {
        printf("Incorrect <server_msqid>\n");
        return 1;
    }

    client_msqid = atoi(argv[1]);
    if (server_msqid == 0)
    {
        printf("Incorrect <client_msqid>\n");
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
        struct msgbuf receiver_buf, buf;
        receiver_buf.mtype = msqid;
        char receiver_mtext[256];

        printf("Enter receiver msqid: ");
        scanf("%d", &receiver_buf.receiver);

        printf("Enter receiver mtext: ");
        scanf("%s", receiver_mtext);
        strcpy(receiver_buf.mtext, receiver_mtext);

        if ((msgsnd(server_msqid, &receiver_buf, sizeof(receiver_buf.mtext), 0)) == -1)
        {
            perror("send error");
            return 3;
        }

        printf("waiting...\n");

        if ((msgrcv(client_msqid, &buf, sizeof(buf.mtext), msqid, 0)) == -1)
        {
            perror("msgrcv error");
            return 4;
        }

        printf("received message: %s\n", buf.mtext);
    }

    return 0;
}