#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list_item {
    char *str;
    struct list_item *next, *prev;
};

struct list_item* read(void) {
    struct list_item* list_start = NULL;
    char strbuffer[100];
    int c, cur_index = 0, flag = 1;
    do {
        c = getchar();
        if (c != ' ' && c != '\n' && c != '\t') {
            strbuffer[cur_index++] = c;
        }
        else {
            strbuffer[cur_index] = 0;
            struct list_item* current_list_item = (struct list_item*) calloc(1, sizeof(struct list_item));
            current_list_item->str = (char*) calloc(strlen(strbuffer) + 1, sizeof(char));
            strcpy(current_list_item->str, strbuffer);

            if (flag) {
                list_start = current_list_item;
                current_list_item->next = list_start;
                current_list_item->prev = list_start;
                flag = 0;
            }
            else {
                current_list_item->next = list_start;
                current_list_item->prev = list_start->prev;
                list_start->prev->next = current_list_item;
                list_start->prev = current_list_item;
            }
            cur_index = 0;
        }
    } while (c != EOF && c != '\n');
    return list_start;
}

void output(struct list_item* start) {
    struct list_item* element = start;
    while (1) {
        printf("%s ", element->str);
        element = element->next;
        if (element == start) break;
    }
    printf("\n");
}

void process(struct list_item** list, const char* s) {
    struct list_item* current_item = *list, * head = *list, * tail = *list;
    do {
        if (strstr(current_item->str, s) != NULL) {
            // duplicate
            for (int i = 0, len = strlen(current_item->str); i < len; ++i) {
                struct list_item* new_item = (struct list_item*)calloc(1, sizeof(struct list_item));
                new_item->str = (char*)calloc((strlen(current_item->str) + 1), sizeof(char));
                strcpy(new_item->str, current_item->str);

                new_item->prev = current_item;
                new_item->next = current_item->next;
                current_item->next->prev = new_item;
                current_item->next = new_item;
                current_item = current_item->next;
            }

            current_item = current_item->next;
            continue;
        }

        struct list_item* tempitem = current_item;
        do {
            struct list_item* temp_next = tempitem->next;
            char* t = tempitem->str;
            tempitem->str = temp_next->str;
            temp_next->str = t;
            tempitem = temp_next;
        } while (tempitem != head->prev);
        tail = tail->prev;
    } while (current_item != tail);
}


int main(int argc, const char ** argv) {
    struct list_item* list = read();
    const char * input_second_string = "abc";
    output(list);
    process(&list, input_second_string);
    output(list);
    return 0;
}
