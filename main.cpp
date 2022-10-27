#include <cstdio>
#include <string>
#include "include/Vector.h"

int main() {
    std::string vec;
    ////sprawdzenie przemiennosci
    Vector v1 = Vector(5,4,3);
    Vector v1c = v1.copy();
    Vector v2 = Vector(1,2,3);
    v1.add(v2);
    printf("%s + %s = %s\n", v1c.str().c_str(), v2.str().c_str(), v1.str().c_str());

    Vector v3 = Vector(5,4,3);
    Vector v4 = Vector(1,2,3);
    v4.add(v3);
    printf("%s + %s = %s \n", v2.str().c_str(), v1c.str().c_str(), v4.str().c_str());


    if(v1.equals(v4)) {
        printf("Dodawanie jest przemienne \n");
    }
    else {
        printf("Dodawanie niejest przemienne \n");
    }
    printf("\n");

    ////obliczanie kąta
    Vector v5 = Vector(0,3,0);
    Vector v6 = Vector(5,5,0);
    printf("kat miedzy wektorami %s i %s (w stopniach): \n%f \n", v5.str().c_str(), v6.str().c_str(), v5.findAngle(v6));
    printf("\n");

    ////wektor prostopadły
    Vector v7 = Vector(4,5,1);
    Vector v8 = Vector(4,1,3);
    Vector perp = v7.cross(v8);
    printf("wektor prostopadly do %s i %s: \n%s \n", v7.str().c_str(), v8.str().c_str(), perp.str().c_str());
    printf("\n");

    printf("%s dot %s = %f \n", v7.str().c_str(), perp.str().c_str(), v7.dot(perp));
    printf("%s dot %s = %f \n", v8.str().c_str(), perp.str().c_str(), v8.dot(perp));
    printf("\n");

    ////normalizacja wektora
    Vector normalised = perp.normalise();
    printf("wektor %s znormalizowany: %s \n", perp.str().c_str(), normalised.str().c_str());
    printf("dlugosc wektora znormalizowanego: %f \n", normalised.length());

    return 0;
}
