#ifndef QUICKUNION_HPP
#define QUICKUNION_HPP

class QuickUnionUF {
public:
    QuickUnionUF(int N);
    bool connected(int p, int q);
    void union_(int p, int q);

    ~QuickUnionUF() { delete [] id; }

private:
    int *id;
    int *sz;

    int root(int i);
};

#endif // QUICKUNION_HPP
