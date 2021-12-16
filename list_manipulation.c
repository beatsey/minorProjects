/*
Во входном файле input.txt записаны две строки, каждая из которых содержит последовательность из не более чем 10000 целых чисел. Обе последовательности заканчиваются числом -1 (и оно не входит в последовательность), остальные числа неотрицательны и не превосходят 10^9. Требуется в файл output.txt вывести без изменения порядка все члены второй последовательности, кроме тех которые встречаются в первой последовательности.

Указание: при решении данной задачи запрещается использовать массивы. Для хранения последовательности чисел используйте однонаправленный или двунаправленный список.

Examples
Input in input.txt
1 8 4 12 -1
2 4 1 3 5 8 -1
Output in output.txt
2 3 5
Input in input.txt
3 5 4 2 0 -1
5 3 2 1 0 4 3 -1
Output in output.txt
1

*/

#include <stdio.h>
#include <stdlib.h>

struct List {
    int value;
    struct List* next;
};

int findElemInList(struct List* list, int value) {
    for (; list != NULL; list = list->next)
        if (list->value == value)
            return 1;
    
    return 0;
}

int main(void)
{
    struct List* list = NULL;

    FILE* file = fopen("input.txt", "r");
    int i = -2;

    // Первая строка
    fscanf(file, "%d", &i);
    while ((!feof(file)) && (i != -1)) {

        struct List* elem = list;
        list = malloc(sizeof(struct List));
        list->next = elem;
        list->value = i;

        fscanf(file, "%d", &i);
    }

    FILE* out = fopen("output.txt", "w+");

    // Вторая строка
    fscanf(file, "%d", &i);
    while ((!feof(file)) && (i != -1)) {

        if (!findElemInList(list, i))
            fprintf(out, "%d ", i);

        fscanf(file, "%d", &i);
    }

    fclose(out);
    fclose(file);

    while (list) {
        struct List* elem = list;
        list = list->next;
        free(elem);
    }

    return 0;
}