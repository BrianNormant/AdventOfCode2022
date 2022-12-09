#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef bool (*cmp)(int);

bool any(int* seq, int len, cmp fun) {
    for (int i = 0; i < len;  i++) {
        if (fun(seq[i])) return true;
        //printf("Comparing %d\n", seq[i]);
    }
    return false;
}

bool all(int* seq, int len, cmp fun) {
    for (int i = 0; i < len;  i++) {
        if (!fun(seq[i])) return false;
    }
    return true;
}

cmp* biggerThan(int fixed) {
    cmp* p = malloc(sizeof(cmp));
    bool m(int a) {
        printf("closure: %d > %d\n", a, fixed);
        return (a > fixed);
    }
    *p = m;
    return p;
}

int main() {
    int* ints = malloc(sizeof(int) * 3);
    ints[0] = 8;
    ints[1] = 4;
    ints[2] = 3;
    for (int i = 0; i < 3; i++) printf("%d", ints[i]);
    printf("\n");

    cmp* func = biggerThan(5);

    if (any(ints, 3, *func)) {
        printf("Found at least 1 element bigger than 5\n");
    } else printf("Didn't found 1 :(\n");
    printf("Finished!\n");
}