#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

enum
{
    BUF_SIZE = 256
};

int
check_file(int fd)
{
    // row may be longer than BUF_SIZE
    int n, found_first = 0;
    static char buffer[BUF_SIZE];
    while ((n=read(fd, &buffer, BUF_SIZE-1)) > 0) {
        buffer[n] = '\0';
        char *first_occurance = strchr(buffer, '\n');
        if (first_occurance != NULL) {
            if (found_first) {
                // OK, file has two+ rows
                return 1;
            }
            found_first = 1; // first row is found
            // check for second occurance
            char *second_occurance = strchr(first_occurance+1, '\n');
            if (second_occurance != NULL) {
                // OK, file has two+ rows
                return 1;
            }
        }
    }
    return 0;
}

void
copy_file(int fd_src, int fd_dest)
{
    // copy from the current position of the heads
    int n;
    static char buffer[BUF_SIZE];
    while ((n=read(fd_src, buffer, BUF_SIZE-1)) > 0) {
        buffer[n] = '\0';
        write(fd_dest, buffer, n);
    }
}

void
copy_to_temp_but_second(int fd_input, int fd_temp)
{
    int n;
    static char buffer[BUF_SIZE];
    while ((n=read(fd_input, &buffer, BUF_SIZE-1)) > 0) {
        buffer[n] = '\0';
        char *p_end = strchr(buffer, '\n');
        if (p_end == NULL) {
            // memorize all
            write(fd_temp, &buffer, n);
            continue;
        }
        // found FIRST row
        // shift head to START of the second row
        int row = p_end - buffer + 1;
        write(fd_temp, &buffer, row); // Записываем всё от начала до \n в fd_temp
        lseek(fd_input, row - n, SEEK_CUR); // Устанавливаем указатель в fd_temp на символ после \n
        break;
    }
    while ((n=read(fd_input, &buffer, BUF_SIZE-1)) > 0) {
        buffer[n] = '\0';
        char *p_end = strchr(buffer, '\n');
        if (p_end == NULL) {
            // skip
            continue;
        }
        // found SECOND row
        // shift head to END of the second row
        int row = p_end - buffer + 1;
        lseek(fd_input, row - n, SEEK_CUR);
        break;
    }
    // copy remained characters to fd_temp
    copy_file(fd_input, fd_temp);
}

int
main(int argc, char *argv[])
{
    // argv[1] - file path

    // 1) check if there is second row
    // 2) copy from fd_input to fd_temp without second row
    // 3) copy from fd_temp to fd_input

    int fd_temp, fd_current;

    // create temp file
    char temp_name[] = "tempXXXXXX";
    fd_temp = mkstemp(temp_name); // create temp file
    unlink(temp_name); // removes temp file from the directory

    // open input file for reading
    if ((fd_current = open(argv[1], O_RDONLY)) == -1) {
        // error while creating
        return 1;
    }

    // check if there is two or more rows
    if (check_file(fd_current)) { // Если файл содержит больше одной строки
        lseek(fd_current, 0, SEEK_SET); // reset head after check
        // copy input file to temp file without second row
        copy_to_temp_but_second(fd_current, fd_temp); // КОПИРУЕМ ВСЁ КРОМЕ ВТОРОЙ СТРОКИ ВО ВРЕМЕННЫЙ ФАЙЛ
        // open input file for writing and copy temp file to it
        close(fd_current);
        fd_current = open(argv[1], O_WRONLY | O_TRUNC, 0666); // ОТКРЫВАЕМ ОСНОВНОЙ ФАЙЛ НА ЗАПИСЬ
        lseek(fd_temp, 0, SEEK_SET); // reset head for copy
        copy_file(fd_temp, fd_current); // КОПИРУЕМ СОДЕРЖИМОЕ ВРЕМЕННОГО ФАЙЛА В ТЕКУЩИЙ
    }

    // end program
    close(fd_current);
    close(fd_temp);
    return 0;
}