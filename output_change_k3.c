#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    // argv[0] - this program name
    // argv[1] - new program path
    // argv[2] - file path
    int fd, status;
    if ((fd=open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        // error while creating
        close(fd);
        return 1;
    }
    if (fork() == 0) {
        dup2(fd, STDOUT_FILENO); // copy fd to stdout
        execlp(argv[1], argv[1], NULL); // replace with new program
    } else {
        // father cleans after the son
        wait(&status); // wait for son
        close(fd);
    }
    return 0;
}