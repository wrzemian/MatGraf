#include <iostream>
#include "include/Vector.h"

int main() {
    ////sprawdzenie przemiennosci///////////////////////////////////////
    Vector v1 = Vector(5,4,3);
    Vector v2 = Vector(1,2,3);
    v1.add(v2);
    Vector v3 = Vector(5,4,3);
    Vector v4 = Vector(1,2,3);
    v4.add(v3);
    std::cout<<"v1(x) = "<<v1.getX()<<"  v2(x) = "<<v4.getX()<<"\n";
    std::cout<<"v1(y) = "<<v1.getY()<<"  v2(y) = "<<v4.getY()<<"\n";
    std::cout<<"v1(z) = "<<v1.getZ()<<"  v2(z) = "<<v4.getZ()<<"\n";
    if(v1.getX() == v4.getX() &&
    v1.getY() == v4.getY() &&
    v1.getZ() == v4.getZ()) {
        std::cout<<"przemiennosc dodawania istnieje\n";
    }
    else {
        std::cout<<"przemiennosc dodawania nie istnieje";
    }
    ////////////////////////////////////////////////////////////////////
    ////obliczanie kąta///////////////////////////////////////
    Vector v5 = Vector(0,3,0);
    Vector v6 = Vector(5,5,0);
    std::cout<<"kat miedzy wektorami (w stopniach): "<<v5.findAngle(v6);
    ////////////////////////////////////////////////////////////////////
    return 0;
}
