#include "msgbuf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char *argv[])
{
    int msqid = -1;
    long mtype;

    if (argc != 3)
    {
        printf("Invalid args!\n"
               "Enter %s <msqid> <mtype>\n",
               argv[0]);
        return 1;
    }

    msqid = atoi(argv[1]);
    if (msqid == -1)
    {
        printf("Incorrect <msqid>\n");
        return 1;
    }

    mtype = strtol(argv[2], NULL, 0);
    if (mtype == 0)
    {
        printf("Incorrect <mtype>\n");
        return 1;
    }

    printf("client %ld started...\n", mtype);

    while (1)
    {
        struct msgbuf receiver_buf, my_buf;
        receiver_buf.mtype = 7707;
        char receiver_mtext[256];

        printf("Enter receiver mtype: ");
        scanf("%d", &receiver_buf.receiver);

        printf("Enter receiver mtext: ");
        scanf("%s", receiver_mtext);
        strcpy(receiver_buf.mtext, receiver_mtext);

        if ((msgsnd(msqid, &receiver_buf, sizeof(receiver_buf.mtext), 0)) == -1)
        {
            perror("msgsnd error");
            return 2;
        }

        printf("waiting message with type %ld...\n", mtype);

        if ((msgrcv(msqid, &my_buf, sizeof(my_buf.mtext), mtype, 0)) == -1)
        {
            perror("msgrcv error");
            return 3;
        }
    }

    return 0;
}