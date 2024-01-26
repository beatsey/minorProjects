#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int
main(void)
{
    setbuf(stdin, 0); // disable buferization
    int status;
    int child_count = 0;
    char current_char, first_char;
    scanf("%c", &first_char);
    while (scanf("%c", &current_char) == 1) {
        pid_t child_pid = fork();
        // we can reach the limit of avaiable processes
        if (child_pid == -1) {
            // can't start a new process
            wait(&status); // wait until resources are avaiable
            if (fork() == 0) {
                if (current_char == first_char) {
                    printf("%c%c", current_char, current_char);                    
                }
            }
        }
        if (child_pid == 0) {
            if (current_char == first_char) {
                printf("%c%c", current_char, current_char);
            }
            exit(0);
        }
        child_count++;
        waitpid(-1, &status, WNOHANG);  //kill zombies
    }
    for (int i = 0; i < child_count; i++) {
        wait(NULL);
    }
    printf("\n");
    return 0;
}