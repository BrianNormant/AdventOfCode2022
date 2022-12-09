#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mseq.h"

int main() {
    {
        //Test of my custom sequence
        seq mySeq= newSeq(sizeof(int));
        printf("size: %d\n", mySeq.len);
        for (int i=0; i < 10; i++) {
            int* temp = malloc(sizeof(int));
            temp[0] = i*2;
            addSeq(&mySeq, temp);
        }
        printf("size: %d\n", mySeq.len);
        for (int i=0; i < 10; i++) {
            printf("mySeq[%d]: %d\n",i ,*(int*)getSeq(&mySeq, i));
        }
    }
    return 0;
}