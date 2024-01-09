#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

enum RETURNCODE {
    GOOD,
    DELIMITER,
    ENDOFFILE
};

struct RETURNVALUE {
    enum RETURNCODE returncode;
    char* returnstring;
};

char*** GLOBAL_ARG = NULL;

struct RETURNVALUE myread(void) {
    int c, i = 0, str_size = 8;
    struct RETURNVALUE callresult;
    callresult.returncode = GOOD;
    callresult.returnstring = NULL;

    while ((c = getchar()) != EOF) {
        if (c != ' ') {
            if (c != ';' && c != '\n') {
                if (callresult.returnstring == NULL) callresult.returnstring = (char*) calloc(str_size, sizeof(char));
                
                if (++i >= str_size) {
                    str_size <<= 1;
                    callresult.returnstring = (char*) realloc(callresult.returnstring, str_size * sizeof(char));
                }
                callresult.returnstring[i] = 0;
                callresult.returnstring[i - 1] = c;

                continue;
            }
            
            callresult.returncode = DELIMITER;
            break;
        }

        if (callresult.returnstring) break;
    }
    if (c == EOF) callresult.returncode = ENDOFFILE;
    return callresult;
}


void free_dynamic_memory(void) {
    if (!GLOBAL_ARG) return;
    for (int i = 0; GLOBAL_ARG[i]; ++i) {
        for (int j = 0; GLOBAL_ARG[i][j]; ++j) free(GLOBAL_ARG[i][j]);
        free(GLOBAL_ARG[i]);
    }
    free(GLOBAL_ARG);
}

int main(int argc, const char ** argv) {
    char** myargv = NULL;
    int current_index_argv = 0;
    int current_global_argv = 0;

    atexit(free_dynamic_memory);
    int initial_argvsize = 2;
    int initial_argsize = 2;
    do {
        struct RETURNVALUE result = myread();
        if (result.returnstring != NULL) {
            if (!myargv) { myargv = (char**) calloc(initial_argvsize, sizeof(char**)); }

            if (++current_index_argv >= initial_argvsize) {
                initial_argvsize <<= 1;
                myargv = (char**) realloc(myargv, initial_argvsize * sizeof(char*));
            }
            myargv[current_index_argv] = NULL;
            myargv[current_index_argv - 1] = result.returnstring;
        }

        if (myargv && (result.returncode != GOOD)) {
            if (!GLOBAL_ARG) GLOBAL_ARG = (char***) calloc(initial_argsize, sizeof(char**));
            
            if (++current_global_argv >= initial_argsize) {
                initial_argsize <<= 1;
                GLOBAL_ARG = (char***) realloc(GLOBAL_ARG, initial_argsize * sizeof(char**));
            }

            GLOBAL_ARG[current_global_argv - 1] = myargv;
            myargv = NULL;
            current_index_argv = 0;
            initial_argvsize = 2;
            GLOBAL_ARG[current_global_argv] = NULL;
        }

        if (result.returncode == ENDOFFILE) break;
    } while (1);

    int exitstatus;
    for (int process_num = 0; GLOBAL_ARG[process_num]; process_num++) {
        int pid = fork();
        if (pid == -1) exit(1);
        if (!pid) { execvp(GLOBAL_ARG[process_num][0], GLOBAL_ARG[process_num]); exit(127); }
        wait(&exitstatus);
    }
    if (WIFEXITED(exitstatus)) return WEXITSTATUS(exitstatus);
    if (WIFSIGNALED(exitstatus)) return 128 + WTERMSIG(exitstatus);
    return 1;
}
