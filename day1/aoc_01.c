#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int addToArr(int** array, int size, int element) {
    //Increase the size of the array
    size++; 
    *array = realloc(*array, size * sizeof(int));
    if (!*array) {
        printf("ERROR while resizing array");
        exit(-1);
    }
    //Now add the element at the last position of the array
    *(*array + (size - 1)) = element;

    return size;
}

int foldl(int* array, int size, int (*funcp)(int, int), int start) {
    int curr = start;
    for (int i = 0; i < size; i++) {
        curr = funcp(curr, *(array+i));
    }
    return curr;
}

int max(int a, int b) { return (a>b)?a:b; }
int add(int a, int b) { return (a+b); }
int ascending(const void* a, const void* b) { return ( *(int*)a - *(int*)b );}
int descending(const void* a, const void* b) { return -( *(int*)a - *(int*)b );}

void p1(FILE* fptr) {
    //Read line by line
    const size_t line_size = 300 * sizeof(char); //Max Size of a line
    char* line = malloc(line_size * sizeof(char));

    int nbElf = 1;
    int* elfCals = malloc(nbElf * sizeof(int));
    *elfCals = 0;
    
    while (fgets(line, line_size, fptr)) {
        if (*line == '\n') {
            nbElf = addToArr(&elfCals, nbElf, 0);
        } else {
            int nb;
            sscanf(line, "%d", &nb);
            *(elfCals + nbElf-1) += nb;
        }
    }

    int result = foldl(elfCals, nbElf, &max, 0);
    printf("max is %d\n", result);
}
void p2(FILE* fptr) {
    const size_t line_size = 300 * sizeof(char); //Max Size of a line
    char* line = malloc(line_size * sizeof(char));

    int nbElf = 1;
    int* elfCals = malloc(nbElf * sizeof(int));
    *elfCals = 0;
    
    while (fgets(line, line_size, fptr)) {
        if (*line == '\n') {
            nbElf = addToArr(&elfCals, nbElf, 0);
        } else {
            int nb;
            sscanf(line, "%d", &nb);
            *(elfCals + nbElf-1) += nb;
        }
    }
    qsort(elfCals, nbElf, sizeof(int), &descending);

    int result = foldl(elfCals, 3, add, 0);
    printf("max is %d\n", result);
}

int main() {
    //Grab the file
    FILE* fptr;
    
    fptr = fopen("input1.txt", "r");
    if (!fptr) {
        printf("Failed to open file");
        return -1;
    }
    p1(fptr);
    fclose(fptr);

    fptr = fopen("input1.txt", "r");
    if (!fptr) {
        printf("Failed to open file");
        return -1;
    }
    p2(fptr);
    fclose(fptr);
    return 0;
}