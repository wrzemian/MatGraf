//
// Created by wrzos on 13.10.2022.
//

#include "../include/Vector.h"
#include <cmath>
#include <string>
#include <sstream>

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z), w(0) {}
Vector::Vector(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

Vector::~Vector() = default;


void Vector::add(const Vector& vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    w += vec.w;
}

void Vector::sub(const Vector& vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    w -= vec.w;
}

double Vector::dot(const Vector& vec) const {
    return x * vec.x
         + y * vec.y
         + z * vec.z
         + w * vec.w;
}

Vector Vector::cross(const Vector& vec) const {
    if( w == 0 && vec.getW() == 0)
    return {y * vec.z - z * vec.y,
            z * vec.x - x * vec.z,
            x * vec.y - y * vec.x,
            0};
}

Vector Vector::multpily(double a) const {
    return {a * x,
            a * y,
            a * z,
            a * w};
}

double Vector::length() const {
    return sqrt(x * x
                + y * y
                + z * z
                + w * w);
}

double Vector::findAngle(const Vector& vec) const {
    return acos(this->dot(vec) / (this->length() * vec.length())) * 180 / M_PI;
}

Vector Vector::normalise() const {
    double temp = this->length();
    return {x / temp,
            y / temp,
            z / temp,
            w / temp};
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

double Vector::getW() const {
    return w;
}
std::string Vector::str() const {
    std::stringstream ss;
    if(w!=0)
        ss << "[" << round(x*1000)/1000 << ", " << round(y*1000)/1000 << ", " << round(z*1000)/1000 << ", " << round(w*1000)/1000 << "]";
    else
        ss << "[" << round(x*1000)/1000 << ", " << round(y*1000)/1000 << ", " << round(z*1000)/1000 << "]";
    return ss.str();
}

bool Vector::equals(const Vector& vec) const {
    if (x != vec.x || y != vec.y || z != vec.z || w != vec.w) {
        return false;
    } else {
        return true;
    }
}

Vector Vector::copy() const {
    return {x, y, z, w};
}






