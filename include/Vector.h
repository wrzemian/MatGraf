//
// Created by wrzos on 13.10.2022.
//

#ifndef MATGRAF_VECTOR_H
#define MATGRAF_VECTOR_H


class Vector {
private:
    double x;
    double y;
    double z;
public:
    Vector(double x, double y, double z);
    virtual ~Vector();
    Vector add(const Vector& vec);
    Vector sub(const Vector& vec);
    double dot(const Vector& vec);
    Vector cross(const Vector& vec);
    Vector multpily(double a);
};


#endif //MATGRAF_VECTOR_H
