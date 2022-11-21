/*
fork_currentdate

Родитель создает сына, тот — внука, а тот — правнука.
Правнук передает в канал текущее время, полученное с помощью системного вызова time, в бинарном виде (тип time_t).

Отец, сын и внук считывают время из канала. Процесс-отец выводит на экран строку "Y:????", где ???? заменяются на текущий год, сын — "M:??", где ?? заменяются на текущий месяц в году (от 1 до 12), число всегда выводится с двумя знаками, внук — "D:??", где ?? заменяются на номер дня в месяце, всегда выводящееся с двумя знаками.

Внук должен вывести число первым, сын — вторым, а отец — третьим.
Записывать в канал разрешается только правнуку.


Пример вывода:

D:11
M:09
Y:2001
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
    int fd1[2]; // Used to store two ends of the first pipe
    pipe(fd1);
    
    time_t seconds;
    pid_t child = fork();
    //printf("parent!");
    
    // Родитель
    if (child == 0){
        //printf("child!");
        child = fork();
        // Сын
        if (child == 0){
            //printf("vnuk!");
            // Внук
            if (fork() == 0){
                //printf("pravnuk!");
                // Правнук
                seconds = time(NULL);
                write(fd1[1], &seconds, sizeof(seconds));
                write(fd1[1], &seconds, sizeof(seconds));
                write(fd1[1], &seconds, sizeof(seconds));
            }else{
                wait(NULL);
                read(fd1[0], &seconds, sizeof(seconds));
                struct tm *local = localtime(&seconds);
                printf("D:%d\n", local->tm_mday);
            }
        }else{
            wait(&child);
            read(fd1[0], &seconds, sizeof(seconds));
            struct tm *local = localtime(&seconds);
            int month = local->tm_mon + 1;      // get month of year (0 to 11)
            printf("M:%d\n", month);
        }
    }else{
        wait(&child);
        read(fd1[0], &seconds, sizeof(seconds));
        struct tm *local = localtime(&seconds);
        int year = local->tm_year + 1900;   // get year since 1900
        printf("Y:%d\n", year);
    }
    
    // Родитель должен дождаться завершения всех процессов и завершиться сам с кодом 0.
    //while(wait(NULL) > 0);
    
    //printf("died!");
    close(fd1[1]);
    close(fd1[0]);
    return 0;
}
