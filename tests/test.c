#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(X, Y) (((X) < (Y)) ? (X) : (Y))
#define max(X, Y) (((X) > (Y)) ? (X) : (Y))

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

int add(int** array, int size, int element) {
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

int ascending(const void* a, const void* b) { return ( *(int*)a - *(int*)b );}
int descending(const void* a, const void* b) { return -( *(int*)a - *(int*)b );}

int main() {
    //Testing std sorting method
    {
        int len = 5;
        int* array = malloc(sizeof(int) * len);
        array[0] = 74;
        array[1] = 15;
        array[2] = -7;
        array[3] = 23;
        array[4] = 44;
    
        for (int i = 0; i < len; i++) {printf("i:%d-> %d\n", i, array[i]);}
        printf("\n");
        qsort(array, len, sizeof(int), &ascending);
    
        for (int i = 0; i < len; i++) {printf("i:%d-> %d\n", i, array[i]);}
        printf("\n");
        qsort(array, len, sizeof(int), &descending);
    
        for (int i = 0; i < len; i++) {printf("i:%d-> %d\n", i, array[i]);}
    }
    //testing conversion between char and int
    {
        int i = 97;
        printf("%d -> %c\n", i, (char)i);
        char c = 'z';
        printf("%c -> %d\n", c, (int)c);
        c = 'A';
        printf("%c -> %d\n", c, (int)c);
    }

    //Testing memcpy method
    {
        char* line = "first second";
        int len = strlen(line)/2;
        //printf("%d", len);
        char* s1 = malloc(sizeof(char) * len + 1);
        char* s2 = malloc(sizeof(char) * len + 1);
        memcpy(s1, line, len); s1[len] = '\0';
        memcpy(s2, line + len, len); s2[len] = '\0';
        printf("s1:%s\n", s1);
        printf("s2:%s\n", s2);
    }
    {
        //Testing strtok method
        char s1[] = "19-81,6-19";
        const char s[] = ",";

        char** tokens = getTokens(s1, s, 2);
        for (int i = 0; i < 2; i++) {
            const char c[] = "-";
            char** subTok = getTokens(tokens[i], "-", 2);
            for (int j = 0; j < 2; j++) {
                printf("%s\n", subTok[j]);
            }
        }
        free(tokens);
    }
    {
        // Testing sets
        Set
            a = newSet(1, 4),//.1234.
            b = newSet(1, 4),//.1234.
            c = newSet(0, 3),//0123..
            d = newSet(2, 5),//..2345
            e = newSet(0, 2),//012...
            f = newSet(3, 5),//...345
            g = newSet(0, 5),//012345
            h = newSet(2, 3);//..23..
        printf("Set a size is %d\n", size(a));
        printf("Set e size is %d\n", size(e));
        printf("Set h size is %d\n", size(h));
    }
}