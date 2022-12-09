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