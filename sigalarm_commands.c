#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int GLOBAL_SIGUSR_COUNTER = 0;
int GLOBAL_PIPE_COUNTER = 0;
int GLOBAL_SIGTERM_FLAG = 0;

void SIGTERMFUNC(int _) {
    GLOBAL_SIGTERM_FLAG = 1;
}

void SIGUSR_FUNC(int _) {
    if (!(++GLOBAL_SIGUSR_COUNTER % 3) && ++GLOBAL_PIPE_COUNTER){};
}

int main(int argc, char** argv) {
    setbuf(stdout, 0);
    char** argv1 = &argv[1], **argv2;

    int i = 1;
    while (strcmp(argv[i++], "--") != 0);
    argv2 = &argv[i];
    argv[i - 1] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
        signal(SIGTERM, SIGTERMFUNC);
        signal(SIGUSR1, SIGUSR_FUNC);
        while (1) {
            if (GLOBAL_PIPE_COUNTER) {
                int fd[2];
                if (pipe(fd) == -1) exit(1);

                pid_t pid1 = fork();
                if (pid1 == 0) {
                    dup2(fd[1], 1);
                    close(fd[0]);
                    execvp(argv1[0], argv1);
                    exit(0);
                }

                pid_t pid2 = fork();
                if (pid2 == 0) {
                    dup2(fd[0], 0);
                    close(fd[1]);
                    execvp(argv2[0], argv2);
                    exit(0);
                }

                close(fd[1]);
                close(fd[0]);
                waitpid(pid2, NULL, 0);
                waitpid(pid1, NULL, 0);

                --GLOBAL_PIPE_COUNTER;
                continue;
            }

            if (GLOBAL_SIGTERM_FLAG) exit(0);
            usleep(50);
        }
    }

    int input_number;
    while (scanf("%i", &input_number) == 1) {
        if (input_number == 0) {
            kill(pid, SIGUSR1);
            continue;
        }

        if (input_number > 0) usleep(input_number);
    }

    kill(pid, SIGTERM);
    waitpid(pid, NULL, 0);
    return 0;
}
