#include <cstdio>
#include <string>
#include "include/Vector.h"
#include "include/Matrix.h"

int main() {
//    std::string vec;
//    ////sprawdzenie przemiennosci
//    Vector v1 = Vector(5,4,3);
//    Vector v1c = v1.copy();
//    Vector v2 = Vector(1,2,3);
//    v1.add(v2);
//    printf("%s + %s = %s\n", v1c.str().c_str(), v2.str().c_str(), v1.str().c_str());
//
//    Vector v3 = Vector(5,4,3);
//    Vector v4 = Vector(1,2,3);
//    v4.add(v3);
//    printf("%s + %s = %s \n", v2.str().c_str(), v1c.str().c_str(), v4.str().c_str());
//
//
//    if(v1.equals(v4)) {
//        printf("Dodawanie jest przemienne \n");
//    }
//    else {
//        printf("Dodawanie niejest przemienne \n");
//    }
//    printf("\n");
//
//    ////obliczanie kąta
//    Vector v5 = Vector(0,3,0);
//    Vector v6 = Vector(5,5,0);
//    printf("kat miedzy wektorami %s i %s (w stopniach): \n%f \n", v5.str().c_str(), v6.str().c_str(), v5.findAngle(v6));
//    printf("\n");
//
//    ////wektor prostopadły
//    Vector v7 = Vector(4,5,1);
//    Vector v8 = Vector(4,1,3);
//    Vector perp = v7.cross(v8);
//    printf("wektor prostopadly do %s i %s: \n%s \n", v7.str().c_str(), v8.str().c_str(), perp.str().c_str());
//    printf("\n");
//
//    printf("%s dot %s = %f \n", v7.str().c_str(), perp.str().c_str(), v7.dot(perp));
//    printf("%s dot %s = %f \n", v8.str().c_str(), perp.str().c_str(), v8.dot(perp));
//    printf("\n");
//
//    ////normalizacja wektora
//    Vector normalised = perp.normalise();
//    printf("wektor %s znormalizowany: %s \n", perp.str().c_str(), normalised.str().c_str());
//    printf("dlugosc wektora znormalizowanego: %f \n", normalised.length());

    double values[16] = {0,1,2,3,
                        4,5,6,7,
                        8,9,10,11,
                        12,13,14,15};
    double values2[16] = {1,2,1,2,
                          1,2,1,2,
                          1,2,1,2,
                          1,2,1,2};
    ////dodawanie, odejmowanie, mnozenie przez skalar
    Matrix m1 = Matrix(values);
    printf("matrix D: \n%s", m1.str().c_str());
    m1.add(Matrix(values));
    printf("\nmatrix D + D: \n%s", m1.str().c_str());
    Matrix m2 = Matrix(values);
    m2.sub(Matrix(values));
    printf("\nmatrix D - D: \n%s", m2.str().c_str());
    Matrix m3 = m1.multpily(4);
    printf("\nmatrix D * 4: \n%s", m3.str().c_str());

    ////sprawdzenie przemiennosci mnozenia
    Matrix A = Matrix(values);
    printf("\n\nmatrix A: \n%s", A.str().c_str());
    Matrix B = Matrix(values2);
    printf("\nmatrix B: \n%s", B.str().c_str());
    Matrix resultAB = A.multiplyByMatrix(B);
    Matrix resultBA = B.multiplyByMatrix(A);
    printf("\nmatrix A*B: \n%s", resultAB.str().c_str());
    printf("\nmatrix B*A: \n%s", resultBA.str().c_str());
    if(resultAB.equals(resultBA))
        printf("\nMnozenie jest przemienne \n");
    else
        printf("\nMnozenie nie jest przemienne \n");

    ////transpozycja
    Matrix transpose = resultBA.transpose();
    printf("\nmatrix B*A transposed: \n%s", transpose.str().c_str());

    ////macierz jednostkowa
    transpose.readyIdentity();
    printf("\nidentity matrix: \n%s", transpose.str().c_str());

    ////wyznacznik
    double niceDetValues[16] = {1,1,-1,1,
                               2,2,-2,1,
                               -2,4,-2,-2,
                               2,-2,2,6};
    Matrix matrix = Matrix(niceDetValues);
    printf("\n\nmatrix C: \n%s", matrix.str().c_str());
    printf("\ndet(C) = %f", matrix.getDeterminant());

    ////macierz odwrotna
    Matrix inversed = matrix.inverse();
    printf("\n\n(c)^-1: \n%s", inversed.str().c_str());

    ////translacja
    Vector v1 = Vector(5,4,3, 1);
    Matrix operation = Matrix(niceDetValues);
    operation.readyTranslation(v1);
    printf("\n\noperation vector: %s \noperation matrix: \n%s", v1.str().c_str(), operation.str().c_str());

    ////skalowanie
    operation.readyScale(v1);
    printf("\nscale matrix: \n%s", operation.str().c_str());

    ////obroty
    Vector v2 = Vector(2,1,3, 1);
    operation.readyRotationAxis(v2, 90);
    printf("\n\nrotation vector: %s\nrotation angle = 90 \nrotation matrix: \n%s", v1.str().c_str(), operation.str().c_str());
    operation.readyRotationX(90);
    printf("\nrotation (X, 90) matrix: \n%s", operation.str().c_str());
    operation.readyRotationY(90);
    printf("\nrotation (Y, 90) matrix: \n%s", operation.str().c_str());
    operation.readyRotationZ(90);
    printf("\nrotation (Z, 90) matrix: \n%s", operation.str().c_str());

    ////zad3
    Vector vec = Vector(1,0,0,1);
    Matrix rotation = Matrix(niceDetValues);
    rotation.readyRotationY(90);
    Vector rotatedVec = rotation.multiplyByVector(vec);
    printf("\n\n%s rotated (Y, 90): %s", vec.str().c_str(), rotatedVec.str().c_str());
    return 0;
}
