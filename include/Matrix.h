//
// Created by wrzos on 08.11.2022.
//

#ifndef MATGRAF_MATRIX_H
#define MATGRAF_MATRIX_H

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "Vector.h"

class Matrix {
private:
    double entries[4][4]{};

    void getCofactor(double matrix[4][4], double temp[4][4], int p, int q, int n);
    double getDeterminant(double matrix[4][4], int n);
    void adjoint(double A[4][4], double adj[4][4]);
public:
    explicit Matrix(const double inValues[]);

    void add(Matrix m);
    void sub(Matrix m);
    Matrix multpily(double a) const;
    Matrix multiplyByMatrix(Matrix m);
    Vector multiplyByVector(Vector v);

    Matrix transpose();
    double getDeterminant();
    Matrix inverse();


    void readyIdentity();
    void readyTranslation(Vector translationVec);
    void readyScale(Vector scaleVec);
    void readyRotationAxis(Vector axis, double angle);
    void readyRotationX(double angle);
    void readyRotationY(double angle);
    void readyRotationZ(double angle);



    std::string str() const;
    bool equals(Matrix m);

    double getEntry(int i, int j);

};


#endif //MATGRAF_MATRIX_H
