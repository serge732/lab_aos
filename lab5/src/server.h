#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct server_msg
{
    int sender_msqid;
    long mtype;
    char mtext[256];
};

int send(int msqid, int sender_msqid, long mtype, char *mtext)
{
    struct server_msg buff;
    buff.sender_msqid = sender_msqid;
    buff.mtype = mtype;
    strcpy(buff.mtext, mtext);

    if ((msgsnd(msqid, &buff, sizeof(buff.mtext), 0)) == -1)
    {
        return -1;
    }

    return 0;
}
