//
// Created by wrzos on 13.10.2022.
//

#include "../include/Vector.h"
#include <iostream>
Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

Vector::~Vector() {

}

void Vector::add(const Vector& vec) {
    x+=vec.x;
    y+=vec.y;
    z+=vec.z;
}

void Vector::sub(const Vector& vec) {
    x-=vec.x;
    y-=vec.y;
    z-=vec.z;
}

double Vector::dot(const Vector& vec) {
    return x*vec.x + y*vec.y + z*vec.z;
}

Vector Vector::cross(const Vector& vec) {
    return {y*vec.z - z*vec.y,
            z*vec.x - x*vec.z,
            x*vec.y - y*vec.x};
}

Vector Vector::multpily(double a) {
    return {a*x,a*y,a*z};
}

double Vector::getX() const {
    return x;
}

double Vector::getY() const {
    return y;
}

double Vector::getZ() const {
    return z;
}
