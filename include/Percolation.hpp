/***********************************Percolation.hpp**********************************
*                                   Percolation.hpp                                 *
*                                                                                   *
* @authr         :    Walter Capa                                                    *
* Descripcion    :    Has all the necessary percolation functions                   *
*                                                                                   *
* @param Percolation(N):    Creates an N-by-N grid                                   *
* @param open(i, j)    :    Opens the sites                                          *
* @param isOpen(i, j)  :    Checks if the site is open                               *
* @param isFull(i, j)  :    CHecks if the site is connected to the first row         *
* @param percolates()  :    Checks if the system percolates                          *
*                                                                                   *
*                                                                                   *
*************************************************************************************/

#ifndef PERCOLATION_HPP
#define PERCOLATION_HPP

#include "QuickUnion.hpp"

class Percolation
{
public:
    Percolation(int N);             // create N-by-N grid, with all sites blocked
    void open(int i, int j);       // open site (row i, column j) if it is not already
    bool isOpen(int i, int j);     // is site (row i, column j) open?
    bool isFull(int i, int j);     // is site (row i, column j) full?
    bool percolates();              // does the system percolate?
    ~Percolation();                  // destroys the array
protected:
private:
    bool ** grid;
    int N;

    QuickUnionUF uf;
    QuickUnionUF uf2;

    int xyTo1D(int i, int j);
};

#endif // PERCOLATION_HPP
