#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char** getTokens(char of[], const char token[], int nbToken) {
    char** result = malloc(sizeof(char*) * nbToken);
    //memset(result, 0, sizeof(char*) * nbToken); //It should work but not garanted by the C standard
    for (int i = 0; i < nbToken; i++) result[i] = NULL;

    result[0] = strtok(of, token);
    for (int i = 1; i < nbToken; i++) {
        result[i] = strtok(NULL, token);
        if (!result[i]) break;
    }
    return result;
}

void p1(FILE* fptr) {
    int chkcycle(int a) {
        return (a == 20 ||
                a == 60 ||
                a == 100 ||
                a == 140 ||
                a == 180 ||
                a == 220);
    };
    const size_t line_size = 300 * sizeof(char); //Max Size of a line
    char* line = malloc(line_size * sizeof(char));
    int cycle = 1;
    int regX = 1;
    char** instruction;
    int sum = 0;
    //The instruction consist of two part, the first eather "noop" or "addx"
    //The second optional, argument, an integer
    while (fgets(line, line_size, fptr)) {
        //printf("During Cycle: %d X : %d\n", cycle, regX);
        if (chkcycle(cycle)) sum += cycle * regX;
        instruction = getTokens(line, " ", 2);
        if (strcmp(instruction[0], "addx") == 0) {
            int n;
            sscanf(instruction[1], "%d", &n);

            //printf("After Cycle: %d X : %d\n", cycle, regX);
            cycle++;
            //printf("During Cycle: %d X : %d\n", cycle, regX);
            if (chkcycle(cycle)) sum += cycle * regX;
            regX += n;
        }
        //printf("After Cycle: %d X : %d\n", cycle, regX);
        cycle++;
    }
    printf("Sum is %d\n", sum);
    free(instruction);
    free(line);
}

void p2(FILE* fptr) {
    const size_t line_size = 300 * sizeof(char); //Max Size of a line
    char* line = malloc(line_size * sizeof(char));
    char** instruction; 
    bool screen[240];
    memset(screen, 1, sizeof(bool) * 240);
    int cycle = 1;
    int regX = 1;
    while (fgets(line, line_size, fptr)) {
        //During Cycle
        screen[cycle-1] = 
            (cycle-1)%40 >= regX-1 &&
            (cycle-1)%40 <= regX+1;
        instruction = getTokens(line, " ", 2);
        if (strcmp(instruction[0], "addx") == 0) {
            int n;
            sscanf(instruction[1], "%d", &n);

            //After Cycle
            cycle++;
            //During Cycle
            screen[cycle-1] = 
                (cycle-1)%40 >= regX-1 &&
                (cycle-1)%40 <= regX+1;
            regX += n;
        }
        //After Cycle
        cycle++;
    }
    free(instruction);
    free(line);

    printf("Screen:\n");
    for (int i = 0; i < 240; i++) {
        if (i % 40 == 0) printf("\n");
        printf("%c", (screen[i])?'#':' ');
    }
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