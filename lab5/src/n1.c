#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <time.h>

typedef struct msqp
{
    long mtype;
    char mtext[256];
} msqp;

int main(int argc, char *argv[])
{
    key_t key = ftok(argv[0], 7);
    if (key == -1)
    {
        perror("ftok error");
        return 1;
    }

    int msqid = msgget(key, 0666 | IPC_CREAT);
    if (msqid == -1)
    {
        perror("msgget error");
        return 2;
    }

    msqp buff;

    buff.mtype = 77;
    strcpy(buff.mtext, "hello");
    if ((msgsnd(msqid, &buff, sizeof(buff.mtext), 0)) == -1)
    {
        perror("msgsnd error");
        return 3;
    }

    memset(buff.mtext, 0, sizeof(buff.mtext));

    buff.mtype = 11;
    strcpy(buff.mtext, "world");
    if ((msgsnd(msqid, &buff, sizeof(buff.mtext), 0)) == -1)
    {
        perror("msgsnd error");
        return 3;
    }

    struct msqid_ds ds;
    if ((msgctl(msqid, IPC_STAT, &ds)) == -1)
    {
        perror("msqctl error");
        return 4;
    }

    printf("msqid: %d\n", msqid);
    printf("uid: %u\n", ds.msg_perm.uid);
    printf("gid: %u\n", ds.msg_perm.gid);
    printf("cid: %u\n", ds.msg_perm.cuid);
    printf("cgid: %u\n", ds.msg_perm.cgid);
    printf("Read/write permission: (%3o)\n", ds.msg_perm.mode & 0777);
    printf("stime: %s", ctime(&ds.msg_stime));
    printf("rtime: %s", ctime(&ds.msg_rtime));
    printf("ctime: %s", ctime(&ds.msg_ctime));
    printf("cbytes: %ld\n", ds.msg_cbytes);
    printf("qnum: %ld\n", ds.msg_qnum);
    printf("qbytes: %ld\n", ds.msg_qbytes);
    printf("lspid: %d\n", ds.msg_lspid);
    printf("lrpid: %d\n", ds.msg_lrpid);

    return 0;
}
