#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct {
    long mtype;
    int data;
} IPC_MSG;

void son(int fd, char* filename) {
    key_t key_msg = ftok(filename, '1');
    int msgid = msgget(key_msg, 0);

    IPC_MSG msg;
    msg.data = 0;

    int num;
    while (1) {
        msgrcv(msgid, &msg, sizeof(int), getpid(), 0);
        lseek(fd, -sizeof(int), SEEK_CUR);
        if (read(fd, &num, sizeof(int))) {};
        if (num == 0) {
            msg.mtype = getppid();
            msgsnd(msgid, &msg, sizeof(int), 0);
            break;
        }
        --num;
        if (write(fd, &num, sizeof(int)) == -1) exit(1);
        msg.mtype = getppid();
        msgsnd(msgid, &msg, sizeof(int), 0);
    }

    close(fd);
    exit(0);
}

int MESSAGE_ID, fd;
int* GLOBAL_ARRAY_CHILDREN;

void HANDLER(int _) {
    msgctl(MESSAGE_ID, IPC_RMID, 0);
    free(GLOBAL_ARRAY_CHILDREN);
    close(fd);
    exit(0);
}

int main(int argc, char** argv) {
    signal(SIGINT, HANDLER);
    int N, K;
    if (scanf("%i %i", &N, &K) != 2) exit(1);

    char filename[] = "123XXXXXX";
    fd = mkstemp(filename);
    unlink(filename);

    key_t key_msg = ftok(argv[0], '1');
    MESSAGE_ID = msgget(key_msg, 0666 | IPC_CREAT);

    GLOBAL_ARRAY_CHILDREN = (int*)calloc(N, sizeof(int));
    if (write(fd, &K, sizeof(int))) {};
    for (int i = 0; i < N; ++i) {
        int pid = fork();
        if (pid == 0) son(fd, argv[0]);
        GLOBAL_ARRAY_CHILDREN[i] = pid;
    }

    IPC_MSG msg_from_father;
    msg_from_father.data = 0;
    for (int i = 0, Z = K + N; i < Z; ++i) {
        msg_from_father.mtype = GLOBAL_ARRAY_CHILDREN[i % N];
        msgsnd(MESSAGE_ID, &msg_from_father, sizeof(int), 0);
        msgrcv(MESSAGE_ID, &msg_from_father, sizeof(int), getpid(), 0);
    }

    while (wait(NULL) > 0);
    lseek(fd, 0, SEEK_SET);
    while (read(fd, &K, sizeof(int)) > 0) printf("%d\n", K);

    msgctl(MESSAGE_ID, IPC_RMID, 0);
    free(GLOBAL_ARRAY_CHILDREN);
    close(fd);
    return 0;
}
