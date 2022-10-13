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

public:
    Vector(double x, double y, double z);
    virtual ~Vector();

    std::string str();
    Vector copy();

    void add(const Vector& vec);
    void sub(const Vector& vec);
    double dot(const Vector& vec);
    Vector cross(const Vector& vec);
    Vector multpily(double a);

    double length();
    double findAngle(Vector vec);
    Vector normalise();
    bool equals(const Vector& vec);

    double getX() const;
    double getY() const;
    double getZ() const;
};


#endif //MATGRAF_VECTOR_H
