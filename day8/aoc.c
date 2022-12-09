#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef bool (*cmp)(int);

bool any(int* seq, int len, cmp fun) {
    for (int i = 0; i < len;  i++) {
        if (fun(seq[i])) return true;
    }
    return false;
}

bool all(int* seq, int len, cmp fun) {
    for (int i = 0; i < len;  i++) {
        if (!fun(seq[i])) return false;
    }
    return true;
}

int howManyBefore(int* seq, int len, cmp fun) {
    for (int i = 0; i < len; i++) {
        if (fun(seq[i])) return i+1;
    }
    return len;
}

int countUntil(int* seq, int len, cmp fun) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        count++;
        if (fun(seq[i])) break;
    }
    return count;
}

int howMany(int* seq, int len, cmp fun) {
    int many = 0;
    for (int i = 0; i < len; i++)
        if (fun(seq[i])) many++;
    return many;
}

void show(int* seq, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d|", seq[i]);
    }
}

void p1(FILE* fptr) {
    const size_t line_size = 300 * sizeof(char); //Max Size of a line
    char* line = malloc(line_size * sizeof(char));
    int* forest = NULL; int len, count = 0;
    while (fgets(line, line_size, fptr)) {
        if (!forest) {
            len = strlen(line) - 1;
            forest = malloc(len * len * sizeof(int));
        }

        for (int i = 0; i < len; i++) {
            char c[2]; 
            c[0] = line[i];
            c[1] = '\0';
            sscanf(c, "%d", &forest[count*len + i]);
        }
        count ++;
    }
    printf("len: %d\n", len);
    int nbVisible = 0;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            int lgn = i;
            int cln = j;
            bool isOnTop, isOnBottom, isOnLeft, isOnRight;
            isOnTop = lgn == 0;
            isOnBottom = lgn == len-1;
            isOnLeft = cln == 0;
            isOnRight = cln == len-1;

            if (isOnTop || isOnBottom || isOnLeft || isOnRight) { //Is on edge?
                nbVisible++;
                //printf("%d is on edges\n", forest[len * i + j]);
            } else {
                // The tree is not on the edge
                //A tree is visible if all of the other trees between it and an edge of the grid are shorter than it
                int* allTreeUp = malloc(sizeof(int) * lgn);
                int* allTreeDown = malloc(sizeof(int) * (len-lgn-1));
                int* allTreeLeft = malloc(sizeof(int) * cln);
                int* allTreeRight = malloc(sizeof(int) * (len-cln-1));

                //printf("For the inner tree %d at (%d %d)\n", forest[len * i + j], i, j);

                //printf("Above:");
                for (int k = 0; k < lgn; k++) {
                    allTreeUp[k] = forest[len * k + j];
                    //printf("%d", allTreeUp[k]);
                } //printf("\n");

                //printf("Bellow:");
                for (int k = 0; k < len-lgn-1; k++) {
                    allTreeDown[k] = forest[len * (k+i+1) + j];
                    //printf("%d", allTreeDown[k]);
                } //printf("\n");

                //printf("Left:");
                for (int k = 0; k < cln; k++) {
                    allTreeLeft[k] = forest[len * i + k];
                    //printf("%d", allTreeLeft[k]);
                } //printf("\n");

                //printf("Right:");
                for (int k = 0; k < len-cln-1; k++) {
                    allTreeRight[k] = forest[len * i + (k+j+1)];
                    //printf("%d", allTreeRight[k]);
                } //printf("\n");

                bool fun(int tree) {
                    //printf("%d>%d\n", tree, forest[len*i+j]);
                    return tree < forest[len * i + j];
                };

                if (all(allTreeUp, lgn, fun) ||
                   all(allTreeDown, len-lgn-1, fun) ||
                   all(allTreeLeft, cln, fun) ||
                   all(allTreeRight, len-cln-1, fun)) {
                    //printf("%d is visible\n", forest[len * i + j]);
                    nbVisible++;
                }
                free(allTreeUp);
                free(allTreeDown);
                free(allTreeLeft);
                free(allTreeRight);
            }
        }
    }
    printf("%d trees visible\n", nbVisible);
    if (forest) free(forest);
    free(line);
}

void p2(FILE* fptr) {
    const size_t line_size = 300 * sizeof(char); //Max Size of a line
    char* line = malloc(line_size * sizeof(char));
    int* forest = NULL; int len, count = 0;
    
    while (fgets(line, line_size, fptr)) {
        if (!forest) {
            len = strlen(line) - 1;
            forest = malloc(len * len * sizeof(int));
        }

        for (int i = 0; i < len; i++) {
            char c[2]; 
            c[0] = line[i];
            c[1] = '\0';
            sscanf(c, "%d", &forest[count*len + i]);
        }
        count ++;
    }

    int max = 0;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            int lgn = i;
            int cln = j;
            bool isOnTop, isOnBottom, isOnLeft, isOnRight;
            isOnTop = lgn == 0;
            isOnBottom = lgn == len-1;
            isOnLeft = cln == 0;
            isOnRight = cln == len-1;

            if (isOnTop || isOnBottom || isOnLeft || isOnRight) { //Is on edge?
                //printf("%d is on edges\n", forest[len * i + j]);
            } else {
                // The tree is not on the edge
                //A tree is visible if all of the other trees between it and an edge of the grid are shorter than it
                int* allTreeUp = malloc(sizeof(int) * lgn);
                int* allTreeDown = malloc(sizeof(int) * (len-lgn-1));
                int* allTreeLeft = malloc(sizeof(int) * cln);
                int* allTreeRight = malloc(sizeof(int) * (len-cln-1));

                //printf("For the inner tree %d at (%d %d)\n", forest[len * i + j], i, j);

                //printf("Above:");
                for (int k = 0; k < lgn; k++) {
                    allTreeUp[(lgn - k - 1)] = forest[len * k + j];
                    //printf("%d", allTreeUp[k]);
                } //printf("\n");

                //printf("Bellow:");
                for (int k = 0; k < len-lgn-1; k++) {
                    allTreeDown[k] = forest[len * (k+i+1) + j];
                    //printf("%d", allTreeDown[k]);
                } //printf("\n");

                //printf("Left:");
                for (int k = 0; k < cln; k++) {
                    allTreeLeft[(cln - k - 1)] = forest[len * i + k];
                    //printf("%d", allTreeLeft[k]);
                } //printf("\n");

                //printf("Right:");
                for (int k = 0; k < len-cln-1; k++) {
                    allTreeRight[k] = forest[len * i + (k+j+1)];
                    //printf("%d", allTreeRight[k]);
                } //printf("\n");

                // Determine the score

                bool fun(int tree) {
                    return tree >= forest[len * i + j];
                }

                int 
                    viewUp = countUntil(allTreeUp, lgn, fun),
                    viewDown = countUntil(allTreeDown, len-lgn-1, fun),
                    viewLeft = countUntil(allTreeLeft, cln, fun),
                    viewRight = countUntil(allTreeRight, len-cln-1, fun);

                int score = viewUp * viewDown * viewRight * viewLeft;
                //printf("(%d, %d):%d->", i, j, forest[len * i + j]);
                //printf("%d*%d*%d*%d=%d\n", viewUp, viewDown, viewLeft, viewRight, score);
                max = (max>score)? max : score;

                free(allTreeUp);
                free(allTreeDown);
                free(allTreeLeft);
                free(allTreeRight);
            }
        }
    }

    printf("len: %d\n", len);
    printf("max score: %d\n", max);
    if (forest) free(forest);
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