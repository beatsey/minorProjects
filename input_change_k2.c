#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    int fd = open(argv[2], O_RDONLY);
    int status;
    if (fd == -1) {
        close(fd);
        return 0;
    }
	// Родительский процесс открывает на чтение файл input.txt,
	// Создаёт сына, сын заменяет свой входной поток данных на  fd и выполняем основную программу
    if (fork() == 0) {
        dup2(fd, STDIN_FILENO);
        execlp(argv[1], argv[1], NULL);
    } else {
        wait(&status);
        close(fd);
    }
    return 0;
}