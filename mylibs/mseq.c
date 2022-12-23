#include <stdio.h>
#include <stdlib.h>

#define IMPL_SEQOF(T) \
typedef struct {\
    unsigned int len;\
    unsigned int cap;\
    T* data;\
} SeqOf_##T;\
\
SeqOf_##T newSetOf_##T() {\
    SeqOf_##T result;\
    result.len = 0;\
    result.cap = 2;\
    result.data = malloc(sizeof(T) * result.cap);\
    return result;\
}\
\
void add_##T(SeqOf_##T* seq, T e) {\
    if (seq->len + 1 > seq->cap) {\
        seq->cap *= 2;\
        seq->data = realloc(seq->data, sizeof(T) * seq->cap);\
    }\
    seq->data[seq->len] = e;\
    seq->len++;\
}\
\
T get_##T(SeqOf_##T* seq, int index) {\
    return seq->data[index];\
}\
void delSeqOf_##T(SeqOf_##T* seq) {\
    free(seq->data);\
}


IMPL_SEQOF(int);
int main(int argc, char const *argv[]) {
    printf("Hello world\n");
    SeqOf_int s = newSetOf_int();
    add_int(&s, 5);
    add_int(&s, 8);
    add_int(&s, -15);

    for (int i = 0; i < s.len; ++i) {
        printf("[%d]:%d\n", i, get_int(&s, i));
    }
    delSeqOf_int(&s);
    for (int i = 0; i < s.len; ++i) {
        printf("[%d]:%d\n", i, get_int(&s, i));
    }


    return 0;
}