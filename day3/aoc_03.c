#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int letterPriority(int i) {
    return i - ((i<97)?38:96);
}

void p1(FILE* fptr) {
    const size_t line_size = 300 * sizeof(char); //Max Size of a line
    char* line = malloc(line_size * sizeof(char));
    int total = 0;
    while (fgets(line, line_size, fptr)) {
        char *s1, *s2; int len = (strlen(line)-1)/2;
        s1 = malloc(sizeof(char) * (len));
        s2 = malloc(sizeof(char) * (len));
        memcpy(s1, line, len);
        memcpy(s2, line + len, len);
        //Iterate through A B C ... x y z
        for (int i = 65; i < 123; i++) {
            if (memchr(s1, (char)i, len) &&
                memchr(s2, (char)i, len)) {
                total += letterPriority(i);
                break;
            }
        }
        free(s1);
        free(s2);
    }
    printf("Priority score is %d\n", total);
    free(line);
}

void p2(FILE* fptr) {
    const size_t line_size = 300 * sizeof(char); //Max Size of a line
    char* line = malloc(line_size * sizeof(char));
    char* elves[3]; int lens[3];
    for (int i = 0; i < 3; i++)
        elves[i] = malloc(line_size * sizeof(char));
    int total = 0, count = 1;
    while (fgets(line, line_size, fptr)) {
        int len = strlen(line) - 1;
        memcpy(elves[count-1], line, len);
        lens[count-1] = len;
        if (count%3 == 0) {
            for (int i = 65; i < 123; i++) {
                if (memchr(elves[0], (char)i, lens[0]) &&
                    memchr(elves[1], (char)i, lens[1]) &&
                    memchr(elves[2], (char)i, lens[2])) {
                    total += letterPriority(i);
                    break;
                }
            }
            count = 0;
        }
        count++;
    }
    printf("Total of priority is %d\n", total);
    for (int i = 0; i < line_size; i++)
        free(elves[i]); 
    free(line);
}

int main() {
    FILE* fptr;
    
    fptr = fopen("input3.txt", "r");
    if (!fptr) {
        printf("Failed to open file");
        return -1;
    }
    p1(fptr);
    fclose(fptr);

    fptr = fopen("input3.txt", "r");
    if (!fptr) {
        printf("Failed to open file");
        return -1;
    }
    p2(fptr);
    fclose(fptr);

    return 0;
}