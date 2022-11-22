//
// Created by wrzos on 22.11.2022.
//

#ifndef MATGRAF_QUATERNION_H
#define MATGRAF_QUATERNION_H


#include "Vector.h"

class Quaternion {
private:
    double a;
    Vector v;

public:
    Quaternion(double a, const Vector &v);
    Quaternion(double a, double x, double y, double z);
    virtual ~Quaternion();

    void add(Quaternion q);
    void sub(Quaternion q);
    Quaternion mul(Quaternion q);
    Quaternion div(Quaternion q);
    void inverse();

    static Quaternion prepareQuaternion( double angle, const Vector& axis);

    std::string str() const;
    bool equals(const Quaternion& q) const;
    Quaternion copy() const;

    double getA() const;
    const Vector &getV() const;
};


#endif //MATGRAF_QUATERNION_H
