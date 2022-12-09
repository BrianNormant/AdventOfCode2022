#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p1(FILE* fptr) {
    const size_t line_size = 300 * sizeof(char); //Max Size of a line
    char* line = malloc(line_size * sizeof(char));
    while (fgets(line, line_size, fptr)) {}
    free(line);
}

void p2(FILE* fptr) {
    const size_t line_size = 300 * sizeof(char); //Max Size of a line
    char* line = malloc(line_size * sizeof(char));
    while (fgets(line, line_size, fptr)) {
    }
    free(line);
}

int main() {
    FILE* fptr;
    
    fptr = fopen("input.txt", "r");
    if (!fptr) {
        printf("Failed to open file");
        return -1;
    }
    p1(fptr);
    fclose(fptr);

    fptr = fopen("input.txt", "r");
    if (!fptr) {
        printf("Failed to open file");
        return -1;
    }
    p2(fptr);
    fclose(fptr);

    return 0;
}