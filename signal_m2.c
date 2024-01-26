#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int count = 1;

void 
sigint_handler(int s) 
{
    // static int count = 1;
    printf("%d\n", count++);
    if (count == 6) {
        exit(0);
    } else {
        signal(SIGINT, sigint_handler);
    }
}

int 
main(void) 
{
    pid_t pid; 
    signal(SIGINT, sigint_handler); // Когда мы получаем сигнал SIGINT, то должна срабатывать функция sigint_handler
    if ((pid = fork()) == 0) { // Создаём ребёнка, при этом реакция на SIGINT сохраняется.
        while (1) {
            pause(); // Сын останавливает свою работу до тех пор, пока не получит сигнал
        }
    } else {
        for (int i = 0; i < 5; i++) {
            usleep(50); // Ждём 50 микросекунд
            kill(pid, SIGINT); // Отправляем SIGINT сыну
        }
        wait(0); // Ждём пока сын умрёт
    }
    return 0;
}