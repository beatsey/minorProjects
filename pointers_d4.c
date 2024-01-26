#include <stdio.h>
#include <stdlib.h>

double *readarray(int *size) {
    double *array, *current;
    scanf("%i", size);
    array = malloc(*size * sizeof(double));
    current = array;
    for (int i = 0; i < *size; i++) { 
        scanf("%lf", current++);
    }
    return array;
}

void printarray(int size, const double *array) {
    for (; size > 0; size--) {
        printf("%.1lf ", *array++);
    }
    printf("\n");
}

int main(void) {
    int size1, size2;
    double *array1 = readarray(&size1), *array2 = readarray(&size2);
    int i = 0;
    for (double *cur1 = array1; i < size1; i++, cur1++) {
        if (*cur1 < 0) {
            for (double *cur2 = array2 + size2 - 1; cur2 >= array2; cur2--) {
                if (*cur2 > 0) {
                    double tmp = *cur1;
                    *cur1 = *cur2;
                    *cur2 = tmp;
                    break;
                }
            }
            break;
        }
    }
    printarray(size1, array1);
    printarray(size2, array2);
    free(array1);
    free(array2);
}
