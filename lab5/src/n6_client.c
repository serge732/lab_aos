#include "msgbuf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        struct msgbuf receiver_buf, buf;
        receiver_buf.receiver = msqid;
        receiver_buf.mtype = 1;
        strcpy(receiver_buf.mtext, "hello from client");

        if ((msgsnd(server_msqid, &receiver_buf, sizeof(receiver_buf.mtext), 0)) == -1)
        {
            perror("send error");
            return 3;
        }

        if ((msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0)) == -1)
        {
            perror("msgrcv error");
            return 4;
        }

        printf("message from server: %s\n", buf.mtext);

        sleep(2);
    }

    return 0;
}