#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(X, Y) (((X) < (Y)) ? (X) : (Y))
#define max(X, Y) (((X) > (Y)) ? (X) : (Y))

char** getTokens(char of[], const char token[], int nbToken) {
    char** result = malloc(sizeof(char*) * nbToken);

    result[0] = strtok(of, token);
    for (int i = 1; i < nbToken; i++) {
        result[i] = strtok(NULL, token);
    }
    return result;
}

typedef struct _Set {
    int from;
    int to;
}Set;

Set newSet(int from, int to) {
    Set result;
    result.from = from;
    result.to = to;
    return result;
}

int size(const Set a) {
    return a.to - a.from + 1;
}

Set intersection(const Set a, const Set b) {
    Set result;
    result.from = max(a.from, b.from);
    result.to = min(a.to, b.to);
    return result;
}

Set uunion(const Set a, const Set b) {
    Set result;
    result.from = min(a.from, b.from);
    result.to = max(a.to, b.to);
    return result;
}


void p1(FILE* fptr) {
    const size_t line_size = 300 * sizeof(char); //Max Size of a line
    char* line = malloc(line_size * sizeof(char));
    int nbFullyContains = 0;
    while (fgets(line, line_size, fptr)) {
        int sets[4];

        char** tokens = getTokens(line, ",", 2);
        int count = 0;
        for (int i = 0; i < 2; i++) {
            char** subTok = getTokens(tokens[i], "-", 2);
            for (int j = 0; j < 2; j++) {
                sscanf(subTok[j], "%d", &(sets[count]));
                count++;
            }
        }
        Set a = newSet(sets[0], sets[1]);
        Set b = newSet(sets[2], sets[3]);

        if (size(intersection(a,b)) == min(size(a), size(b))) {
            nbFullyContains++;
        }
        free(tokens);
    }
    printf("%d pairs fully contains each other\n", nbFullyContains);
    free(line);
}

void p2(FILE* fptr) {
    const size_t line_size = 300 * sizeof(char); //Max Size of a line
    char* line = malloc(line_size * sizeof(char));
    int nbOverlaps = 0;
    while (fgets(line, line_size, fptr)) {
        int sets[4];

        char** tokens = getTokens(line, ",", 2);
        int count = 0;
        for (int i = 0; i < 2; i++) {
            char** subTok = getTokens(tokens[i], "-", 2);
            for (int j = 0; j < 2; j++) {
                sscanf(subTok[j], "%d", &(sets[count]));
                count++;
            }
        }
        Set a = newSet(sets[0], sets[1]);
        Set b = newSet(sets[2], sets[3]);

        if (size(intersection(a,b)) > 0) {
            nbOverlaps++;
        }
        free(tokens);
    }
    printf("%d pairs overlaps\n", nbOverlaps);
    free(line);
}

int main() {
    FILE* fptr;
    
    fptr = fopen("input4.txt", "r");
    if (!fptr) {
        printf("Failed to open file");
        return -1;
    }
    p1(fptr);
    fclose(fptr);

    fptr = fopen("input4.txt", "r");
    if (!fptr) {
        printf("Failed to open file");
        return -1;
    }
    p2(fptr);
    fclose(fptr);

    return 0;
}