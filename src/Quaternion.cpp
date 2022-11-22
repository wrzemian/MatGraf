//
// Created by wrzos on 22.11.2022.
//

#include "../include/Quaternion.h"
#include <cmath>
#include <stdexcept>
#include <sstream>

Quaternion::Quaternion(double a, const Vector &v) : a(a), v(v) {}

Quaternion::Quaternion(double a, double x, double y, double z) : a(a), v(Vector(x,y,z)) {}
Quaternion::~Quaternion() {

}

double Quaternion::getA() const {
    return a;
}

const Vector &Quaternion::getV() const {
    return v;
}

void Quaternion::add(Quaternion q) {
    this->a += q.a;
    this->v.add(q.v);
}

void Quaternion::sub(Quaternion q) {
    this->a -= q.a;
    this->v.sub(q.v);
}

Quaternion Quaternion::mul(Quaternion q) {
    double tempA = this->a * q.a -  this->v.dot(q.v);
    Vector tempV = q.v.multpily(this->a);
    tempV.add(this->v.multpily(q.a));
    tempV.add(this->v.cross(q.v));
    return {tempA, tempV};
}

Quaternion Quaternion::div(Quaternion q) {
    double a1 = this->a;
    double a2 = q.a;
    Vector v1 = this->v;
    Vector v2 = q.v;
    double divisor = pow(a2, 2) + v2.dot(v2);
    if(divisor == 0) {
        throw std::invalid_argument( "divisor cant be 0" );
    }

    double tempA = a1 * a2 +  v1.dot(v2);
    tempA /= divisor;

    Vector a1v2 = v2.multpily(a1);
    Vector a2v1 = v1.multpily(a2);
    Vector v1v2 = v1.cross(v2);

    a2v1.sub(a1v2);
    a2v1.sub(v1v2);


    return {tempA, a2v1.multpily(1/divisor)};
}

std::string Quaternion::str() const {
    std::stringstream ss;
    ss << round(a*1000)/1000 << " + " << round(v.getX()*1000)/1000 << "i + " << round(v.getY()*1000)/1000 << "j + " << round(v.getZ()*1000)/1000 << "k";
    return ss.str();
}

bool Quaternion::equals(const Quaternion& q) const {
    if (a != q.a || !this->v.equals(q.v)) {
        return false;
    } else {
        return true;
    }
}

Quaternion Quaternion::copy() const {
    return {a, v};
}

static double radians(double angle) {
    return M_PI*angle/180.0;
}

void Quaternion::inverse() {
    this->v.multpily(-1.0);
}

Quaternion Quaternion::prepareQuaternion(double angle, const Vector& axis) {
    double A = cos(radians(angle/2.0));

    double a = axis.getX(), b = axis.getY(), c = axis.getZ();
    double multiplier = sin(radians(angle/2.0)) / sqrt(a*a + b*b + c*c);

    return {A, axis.multpily(multiplier)};
}

