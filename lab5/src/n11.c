#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct msgbuf
{
    long mtype;
    char mtext[256];
};

int msqid = -1;

void sig_handler(int sig)
{
    if ((msgctl(msqid, IPC_RMID, 0)) == -1)
    {
        perror("server msgctl error");
    }
}

int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = sig_handler;
    sigaction(SIGINT, &act, 0);

    msqid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if (msqid == -1)
    {
        perror("msgget error");
        return 1;
    }

    int pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        return 2;
    case 0:
        while (1)
        {
            struct msgbuf receiver_buf, buf;
            receiver_buf.mtype = 1;
            strcpy(receiver_buf.mtext, "hello from child");

            if ((msgrcv(msqid, &buf, sizeof(buf.mtext), 2, 0)) == -1)
            {
                perror("child msgrcv error");
                return 3;
            }

            printf("i'm child. received message: %s\n", buf.mtext);

            if ((msgsnd(msqid, &receiver_buf, sizeof(receiver_buf.mtext), 0)) == -1)
            {
                perror("child msgsnd error");
                return 4;
            }
        }
    default:
        while (1)
        {
            struct msgbuf receiver_buf, buf;
            receiver_buf.mtype = 2;
            strcpy(receiver_buf.mtext, "hello from parent");

            if ((msgsnd(msqid, &receiver_buf, sizeof(receiver_buf.mtext), 0)) == -1)
            {
                perror("parent msgsnd error");
                return 4;
            }

            if ((msgrcv(msqid, &buf, sizeof(buf.mtext), 1, 0)) == -1)
            {
                perror("parent msgrcv error");
                return 3;
            }

            printf("i'm parent. received message: %s\n", buf.mtext);
        }
    }

    return 0;
}