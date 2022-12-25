#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

int main(int argc, char *argv[0])
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
        struct server_msg msg;
        if ((send(server_msqid, msqid, 1, "hello from client")) == -1)
        {
            perror("send error");
            return 3;
        }

        if ((msgrcv(msqid, &msg, sizeof(msg.mtext), 0, 0)) == -1)
        {
            perror("msgrcv error");
            return 4;
        }

        printf("message from server: %s\n", msg.mtext);

        sleep(2);
    }

    return 0;
}