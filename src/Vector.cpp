//
// Created by wrzos on 13.10.2022.
//

#include "../include/Vector.h"
#include <cmath>
#include <stdio.h>
#include <string>
#include <sstream>

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

Vector::~Vector() {}


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

double Vector::length() {
    return sqrt(x*x + y*y + z*z);
}

double Vector::findAngle(Vector vec) {
    return acos(this->dot(vec)/(this->length() * vec.length())) * 180 / M_PI;
}

Vector Vector::normalise() {
    double temp = this->length();
    return {x/temp, y/temp, z/temp};
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

std::string Vector::str() {
    std::stringstream ss;
    ss << "[" << x << ", " << y << ", " << z << "]";
    return ss.str();
}

bool Vector::equals(const Vector& vec) {
    if (x != vec.x || y != vec.y || z != vec.z) {
        return false;
    } else {
        return true;
    }
}

Vector Vector::copy() {
    return Vector(x, y, z);
}




