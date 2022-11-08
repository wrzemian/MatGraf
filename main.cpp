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
    Matrix m1 = Matrix(values);
    m1.add(Matrix(values));
    printf("matrix: \n%s", m1.str().c_str());

    Matrix m2 = Matrix(values);
    m2.sub(Matrix(values));
    printf("\nmatrix: \n%s", m2.str().c_str());

    Matrix m3 = m1.multpily(2);
    printf("\nmatrix: \n%s", m3.str().c_str());

    Matrix m4 = m3.multiplyByMatrix(Matrix(values));
    printf("\nmatrix: \n%s", m4.str().c_str());

    Matrix m5 = m1.transpose();
    printf("\nmatrix: \n%s", m5.str().c_str());

    printf("\ndeterminant: %d", m5.getDeterminant(4));

    m5.loadIdentity();
    printf("\nmatrix: \n%s", m5.str().c_str());
    return 0;
}
