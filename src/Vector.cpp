//
// Created by wrzos on 13.10.2022.
//

#include "../include/Vector.h"

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

Vector::~Vector() {

}

Vector Vector::add(const Vector& vec) {
    return {x+vec.x, y+vec.y, z+vec.z};
}

Vector Vector::sub(const Vector& vec) {
    return {x-vec.x, y-vec.y, z-vec.z};
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

}