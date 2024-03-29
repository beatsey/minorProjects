/*
fork_printsum

Процесс-родитель создает процесса-сына, а тот в свою очеред процесса-внука.
Процесс-родитель и процесс-внук должны быть соединены анонимным каналом в направлении от родителя к внуку.
Процесс-родитель считывает 32-битные знаковые целые числа, подаваемые на стандартном потоке ввода в текстовом виде.
Последовательность заканчивается признаком конца файла.
Процесс-родитель передает считанные числа в канал в бинарном виде.
Процесс-внук считывает числа из канала и вычисляет их сумму.
После чтения всех чисел процесс-внук выводит на стандартный поток вывода их сумму и завершает работу.
Процесс-родитель должен дождаться завершения всех порожденных им процессов и завершиться сам с кодом завершения 0.
Ошибка "Synchronization error" означает, что родитель завершился раньше какого-либо из порожденных им процессов.

Input
1 2 3 4 5 6 7 8 9 10
Output
55
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main()
{
    int fd1[2];
    pipe(fd1);
    
    pid_t child = fork();
    // Родитель
    if (child == 0) {
        child = fork();
        // Сын
        if (child == 0) {
            // Внук
            // Внук закрывает канал на запись
            close(fd1[1]);
            
            int num;
            long long sum = 0;
            while(read(fd1[0], &num, sizeof(num)) > 0) {
                //printf("read %d\n", num);
                sum += num;
            }
            close(fd1[0]);
            printf("%lld\n", sum);
        }else{
            // Сын
            close(fd1[1]);
            close(fd1[0]);
            wait(NULL);
        }
    }else{
        // Родитель
        // Закрыли на чтение
        close(fd1[0]);
        
        int num;
        while(scanf("%d", &num) != EOF)
            write(fd1[1], &num, sizeof(num));
        
        // Закрыли на запись
        close(fd1[1]);
        wait(NULL);
    }
    
    return 0;
}
