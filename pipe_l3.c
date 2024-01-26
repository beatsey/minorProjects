#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int
main(void)
{
    pid_t pid_1, pid_2, pid_3;
    int fd_1[2];
    int fd_2[2];
    pipe(fd_1); // Создаём канал для замены потоков ввода/вывода
    if ((pid_1 = fork()) == 0) {
        dup2(fd_1[1], STDOUT_FILENO); // Выводим теперь в канал fd_1[1]
        close(fd_1[0]);
        close(fd_1[1]);
        execlp("grep", "grep", "^[a-zA-Z0-9_]*(", NULL);
        // Запускаем grep на входном коде. При этом результат grep будет выведен в канал fd_1.
        _exit(1); //Если не произошло фактической замены тела процесса.
    }
    pipe(fd_2);
    if ((pid_2 = fork()) == 0) {
        dup2(fd_1[0], STDIN_FILENO); // Подсоединяем выход grep как вход cut'а
        dup2(fd_2[1], STDOUT_FILENO);
        close(fd_1[0]);
        close(fd_1[1]);
        close(fd_2[0]);
        close(fd_2[1]);
        execlp("cut", "cut", "-d", "(", "-f1", NULL);
        _exit(1); //Если не произошло фактической замены тела процесса.
    }
    close(fd_1[0]); 
    close(fd_1[1]);
    if ((pid_3 = fork()) == 0) {
        dup2(fd_2[0], STDIN_FILENO);
        close(fd_2[0]);
        close(fd_2[1]);
        execlp("sort", "sort", NULL);
        _exit(1); //Если не произошло фактической замены тела процесса.
    }
    close(fd_2[0]);
    close(fd_2[1]);
    waitpid(pid_1, NULL, 0);
    waitpid(pid_2, NULL, 0);
    waitpid(pid_3, NULL, 0);
    return 0;
}