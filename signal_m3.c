#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

unsigned long long number;

void
sigalarm_handler(int s)
{
    printf("%llu\n", number);
    alarm(5);
}

void
sigint_handler(int s)
{
    unsigned int res = alarm(0);
    printf("%d\n", res);
    alarm(res);
}

int
main(void)
{
    scanf("%llu", &number);
    signal(SIGINT, sigint_handler);
    signal(SIGALRM, sigalarm_handler);
    alarm(5); // Устанавливаем отправку сигнала SIGALRM через 5 секунд.
    // При этом НЕ БЛОКИРУЕТСЯ основной поток выполнения
    while (number > 0) {
        number = number - 1;
    }
    return 0;
}