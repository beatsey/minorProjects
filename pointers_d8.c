#include <stdio.h> 
 
int largestint(const char * str, const char ** pointer_to_result) { 
    int size = 1; 
    while(*str && !isdigit(*str)) str++; 
    if (*str == '\0') return 0; 
     
    *pointer_to_result = str; 
    if (*str != '0') while(isdigit(*(str + size))) size++; 
    return size; 
} 
 
int integerscmp(const char * str1, int size1, const char * str2, int size2){ 
    if (size1 < size2) return -1; 
    if (size1 > size2) return 1; 
    while(size1 > 0 && *str1 == *str2) {str1++; str2++; size1--; } 
    if (size1 == 0) return 0; 
    if (*str1 < *str2) return -1; 
    return 1; 
} 
 
int main() { 
    char str1[82]; 
    fgets(str1, 82, stdin); 
    const char * result = str1; 
    const char * max_num_ptr = NULL; 
    int max_num_size = -1; 
    int size; 
    while(size = largestint(result, &result)) { 
        if (integerscmp(max_num_ptr, max_num_size, result, size) < 0){ 
            max_num_ptr = result; 
            max_num_size = size; 
        } 
        result += size; 
    } 
     
    if (max_num_size > 0) printf("%.*s\n", max_num_size, max_num_ptr); 
    else printf("\n"); 
     
    return 0; 
}