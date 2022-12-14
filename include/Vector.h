//
// Created by wrzos on 13.10.2022.
//

#ifndef MATGRAF_VECTOR_H
#define MATGRAF_VECTOR_H

#include <string>

class Vector {

private:
    double x;
    double y;
    double z;
    double w;

public:
    Vector(double x, double y, double z);
    Vector(double x, double y, double z, double w);

    bool operator==(const Vector& vec) const;

    virtual ~Vector();

    std::string str() const;
    Vector copy() const;

    void add(const Vector& vec);
    void sub(const Vector& vec);
    double dot(const Vector& vec) const;
    Vector cross(const Vector& vec) const;
    Vector multpily(double a) const;

    double length() const;
    double findAngle(const Vector& vec) const;
    Vector normalise() const;
    bool equals(const Vector& vec) const;

    double getX() const;
    double getY() const;
    double getZ() const;
    double getW() const;
};


#endif //MATGRAF_VECTOR_H
