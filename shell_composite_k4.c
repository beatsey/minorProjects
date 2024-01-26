#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    // argv[0] - this program name
    // argv[1] - p1
    // argv[2] - p2
    // argv[3] - file path
    // argv[4] - p3
    int fd, status;
    // create file for concatenate
    if ((fd=open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1) {
        // error while creating
        close(fd);
        return 1;
    }
    if (fork() == 0) {
        // p1 || p2 <- if p1 then return, if !p1 then p2 then return
        dup2(fd, STDOUT_FILENO);
        if (fork() == 0) {
            // p1
            execlp(argv[1], argv[1], NULL);
            exit(1);
        }
        wait(&status); // father waits
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // p1 ended correctly
            return 0;
        }
        // p1 ended incorrectly
        if (fork() == 0) {
            // p2
            execlp(argv[2], argv[2], NULL);
            exit(1);
        }
        wait(&status); // father waits
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // p2 ended correctly
            return 0;
        }
        // p2 ended incorrectly
        return 1;
    }
    wait(&status); // wait for (p1 || p2)
    close(fd);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        // p1 || p2 ended correctly
        // start p3 without cat
        if (fork() == 0) {
            execlp(argv[4], argv[4], NULL);
            exit(1);
        }
        wait(&status);
    }
    return 0;
}