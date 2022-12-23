#include <stdio.h>
#include <stdlib.h>

int main() {
    char* i = malloc(sizeof(char));
    while (1) {
        printf("%c\n", *i);
        i++;
    }
}