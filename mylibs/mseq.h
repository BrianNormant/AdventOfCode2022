typedef struct {
    void** data; // pointer to the block of memory containing the data
    int len; // size of the seq
    int cap; // real buffer capacity in byte
    int tlen; // size of each element in byte
    void* first;
} seq;

seq newSeq(int tlen) {
    seq result;
    result.first = malloc(tlen * 10);
    result.data = &result.first;
    result.len = 0;
    result.cap = tlen * 10; // The capacity is always 5 element
    result.tlen = tlen;

    return result;
}

void addSeq(seq* s, void* element) {
    //Check if there are enough place in data
    if (s->cap < (s->len+1)*s->tlen) {
        //Double the capacity if not
        s->cap = s->cap * 2;
        s->first = realloc(s->first, s->cap);
        s->data = &s->first;
    }
    //Add the element to the data
    memcpy(s->first + (s->len * s->tlen), element, s->tlen);
    s->len++;
}

//Return a pointer to the indexth element of the Seq
// /! this is a pointer and modifiying the data will modify the content of the seq
void* getSeq(seq* s,int index) {
    if (index >= s->len) return NULL;
    return s->first + (index * s->tlen);
}

void delSeq(seq* s) {
    free(s->first);
}