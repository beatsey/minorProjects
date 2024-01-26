#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

void
my_process(int number)
{
    FILE *pipeline;
    if (number == 1) {
        while ((pipeline=fopen("pipeline.txt", "r")) == NULL) {
            usleep(1000);
        }
        printf("%d\n", number);
        fclose(pipeline);
        remove("pipeline.txt");
    } else
    if (number == 2) {
        // let us assure that pipeline.txt is not present in the directory
        printf("%d\n", number);
        pipeline = fopen("pipeline.txt", "w+");
        fprintf(pipeline, "second was here");
        fclose(pipeline);
    }
}

int
main(void)
{
    if (fork() == 0) {
        my_process(1);
        exit(0);
    }
    if (fork() == 0) {
        my_process(2);
        exit(0);
    }
    // wait sons to finish
    while(wait(NULL) > 0) {};
    return 0;
}