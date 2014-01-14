#include "../include/QuickUnion.hpp"

QuickUnionUF::QuickUnionUF(int N) {
    id = new int[N];
    for (int i = 0; i < N; i++) {
        id[i] = i;
    }
    sz = new int[N];
    for (int i = 0; i < N; i++) {
        sz[i] = 1;
    }
}

bool QuickUnionUF::connected(int p, int q) {
    return root(p) == root(q);
}

void QuickUnionUF::union_(int p, int q) {
    int i = root(p);
    int j = root(q);
    if (sz[i] < sz[j]) {
        id[i] = j;
        sz[j] += sz[i];
    } else {
        id[j] = i;
        sz[i] += sz[j];
    }
}

int QuickUnionUF::root(int i){
    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}
