//
// Created by wrzos on 08.11.2022.
//

#ifndef MATGRAF_MATRIX_H
#define MATGRAF_MATRIX_H

#include <string>
#include <sstream>

class Matrix {
private:
    double entries[4][4];

    void getCofactor(int temp[4][4], int p, int q, int n);

public:
    explicit Matrix(double inValues[]);

    void add(Matrix m);
    void sub(Matrix m);
    Matrix multpily(double a) const;
    Matrix multiplyByMatrix(Matrix m);

    Matrix transpose();
    void loadIdentity();
    double getDeterminant(int n);


    std::string str() const;

    float getEntry(int i, int j);
};


#endif //MATGRAF_MATRIX_H
