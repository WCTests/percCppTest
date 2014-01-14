#include <iostream>
#include "../include/Percolation.hpp"

Percolation::Percolation(int N) :uf((N * N) + 2), uf2((N * N) + 1)  {
    Percolation::N = N;
    // Creates the 2 dimensions grid
    grid = new bool*[N];
    for (int i = 0; i < N; i++)
        grid[i] = new bool[N];

    // All the sites are false(closed)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = false;
}

void Percolation::open(int i, int j) {

    int site = xyTo1D(i, j);
    int siteL = xyTo1D(i, j - 1);
    int siteR = xyTo1D(i, j + 1);
    int siteU = xyTo1D(i - 1, j);
    int siteD = xyTo1D(i + 1, j);

    // Opens the given site
    if (!isOpen(i, j)) {
        grid[i - 1][j - 1] = true;

        // Connects the site with the sites next to it if they are open
        // If it's not int he first row, it's open and it's not already connected
        if (i > 1 && isOpen(i - 1, j) && !uf2.connected(site, siteU)) {
            uf.union_(site, siteU);
            uf2.union_(site, siteU);
        }
        // If it's not in the last row, it's open and it's not already connected
        if (i < N && isOpen(i + 1, j) && !uf2.connected(site, siteD)) {
            uf.union_(site, siteD);
            uf2.union_(site, siteD);
        }
        // if it's not in the first col, it's open and it's not already connected
        if (j > 1 && isOpen(i, j - 1) && !uf2.connected(site, siteL)) {
            uf.union_(site, siteL);
            uf2.union_(site, siteL);
        }
        // if it's not in the last col, it's open and it's not already connected
        if (j < N && isOpen(i, j + 1) && !uf2.connected(site, siteR)) {
            uf.union_(site, siteR);
            uf2.union_(site, siteR);
        }

        // Connects the virtual sites
        if (i == 1) { uf.union_(site, 0); uf2.union_(site, 0); }
        if (i == N) { uf.union_(site, ((N * N) + 1)); }
    }
}

bool Percolation::isOpen(int i, int j) {
    return grid[i - 1][j - 1];
}
bool Percolation::isFull(int i, int j) {
    return uf2.connected(0, xyTo1D(i, j));
}
bool Percolation::percolates() {
    return uf.connected(0, ((N * N) + 1));
}

Percolation::~Percolation() {
    for (int i = 0; i < N; i++) {
        delete [] grid[i];
    }
    delete [] grid;
}

int Percolation::xyTo1D(int i, int j) {
    return (N * (i - 1)) + j;
}
