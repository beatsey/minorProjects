#include <stdio.h> 
#include <stdlib.h> 
 
enum { 
    RESIZE_MULTIPLIER = 10 
}; 
 
int main(int argc, char* argv[]) { 
    int x, * array, pos = 0; 
    unsigned int size = 1; 
    array = (int*) malloc(size * sizeof(int)); 
 
    while (scanf("%d", &x) == 1) { 
        if (pos == size) { 
           size = size * RESIZE_MULTIPLIER; 
            array = (int*) realloc(array, size * sizeof(int)); 
           if (array == NULL){ exit(1); } 
        } 
        array[pos++] = x; 
    } 
 
    for (; --pos >= 0;) printf("%d ", array[pos]); 
    free(array); 
 
    return 0; 
}