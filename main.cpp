#include <cstdio>
#include <string>
#include <vector>
#include <iomanip>
#include "include/Vector.h"
#include "include/Matrix.h"
#include "include/Quaternion.h"
#include "cmath"
#include <algorithm>

void task1(); void task2(); void task3(); void task4();

struct Line{
    Line() : point(point), vector(vector) {
    }

    Line(Vector p, Vector v) : point(p), vector(v) {
    }

    Vector vector;
    Vector point;
};

struct Plane {
    Vector normal;
    Vector point;
};

struct Sphere {
    Vector center;
    double radius;
};

struct Section {
    Vector A;
    Vector B;
};

struct Box {
    Vector a;
    Vector b;
    Vector c;
    Vector d;
    Vector e;
    Vector f;
    Vector g;
    Vector h;
    std::vector <Plane> planes;
//    Plane abcd; 0
//    Plane abef; 1
//    Plane efgh; 2
//    Plane cdgh; 3
//    Plane aceg; 4
//    Plane bdfh; 5

//    a Vector(15,15,15)
//    b Vector(15,15,-15)
//    c Vector(15,-15,15)
//    d Vector(15,-15,-15)
//    e Vector(-15,15,15)
//    f Vector(-15,15,-15)
//    g Vector(-15,-15,15)
//    h Vector(-15,-15,-15)
};


Line createLine(Vector p1, Vector p2){
    Vector vector = p1.copy();
    vector.sub(p2);

    return {p2, vector};
}

Plane createPlane(Vector p1, Vector p2, Vector p3) {
    Vector vector1 = p1.copy();
    Vector vector2 = p2.copy();
    Vector vector3 = p3.copy();

    vector1.sub(p2);
    vector3.sub(p1);

    return {vector1.cross(vector3), p2};
}

Box createBox(Vector a, Vector b, Vector c, Vector d, Vector e ,Vector f, Vector g, Vector h) {
    Plane acd = createPlane(a, c, d);
    Plane abe = createPlane(a, b, e);
    Plane efh = createPlane(e, f, h);
    Plane cgh = createPlane(c, g, h);
    Plane ace = createPlane(a, c, e);
    Plane bdf = createPlane(b, d, f);
    std::vector <Plane> planes;
    planes.push_back(acd);
    planes.push_back(abe);
    planes.push_back(efh);
    planes.push_back(cgh);
    planes.push_back(ace);
    planes.push_back(bdf);
    return {a, b, c, d, e, f, g, h, planes};
}

double calculateTLinePlane(Line l1, Plane p1) {
    Vector p = l1.point;
    Vector q = p1.point;
    Vector v = l1.vector;
    Vector n = p1.normal;

    Vector minusN = n.multpily(-1);
    p.sub(q);
    double numerator = minusN.dot(p);
    double divisor = n.dot(v);

    if(divisor == 0){
        throw std::invalid_argument( "divisor is equal 0" );
    }

    return numerator / divisor;

}

Vector calculateIntersectionLinePlane(const Line& l, const Plane& p) {
    try {
        double t = calculateTLinePlane(l, p);

        Vector point = l.point;
        Vector vector = l.vector;

        point.add(vector.multpily(t));
        return point;
    }
    catch (const std::invalid_argument& e) {
        return {2137, 2137, 2137};
    }
}

struct vec2D {
    double x;
    double y;
};

vec2D createVec2D( double x, double y) {
    return {x, y};
}

vec2D vectorise(vec2D p1, vec2D p2) {
    return {p2.x - p1.x, p2.y - p1.y};
}

double dot(vec2D u, vec2D v) {
    return u.x * v.x + u.y * v.y;
}


bool pointInRectangleXY(Vector a, Vector b, Vector c, Vector point ) {
    vec2D A = createVec2D(    a.getX(),     a.getY());
    vec2D B = createVec2D(    b.getX(),     b.getY());
    vec2D C = createVec2D(    c.getX(),     c.getY());
    vec2D m = createVec2D(point.getX(), point.getY());

    vec2D AB = vectorise(A, B);
    vec2D AM = vectorise(A, m);
    vec2D AC = vectorise(A, C);
    double dotABAM = dot(AB, AM);
    double dotABAB = dot(AB, AB);
    double dotAMAC = dot(AM, AC);
    double dotACAC = dot(AC, AC);
    return (0 <= dotABAM && dotABAM <= dotABAB && 0 <= dotAMAC && dotAMAC <= dotACAC);
}

bool pointInRectangleYZ(Vector a, Vector b, Vector c, Vector point ) {
    vec2D A = createVec2D(    a.getY(),     a.getZ());
    vec2D B = createVec2D(    b.getY(),     b.getZ());
    vec2D C = createVec2D(    c.getY(),     c.getZ());
    vec2D m = createVec2D(point.getY(), point.getZ());

    vec2D AB = vectorise(A, B);
    vec2D AM = vectorise(A, m);
    vec2D AC = vectorise(A, C);
    double dotABAM = dot(AB, AM);
    double dotABAB = dot(AB, AB);
    double dotAMAC = dot(AM, AC);
    double dotACAC = dot(AC, AC);
    return (0 <= dotABAM && dotABAM <= dotABAB && 0 <= dotAMAC && dotAMAC <= dotACAC);
}

bool pointInRectangleXZ(Vector a, Vector b, Vector c, Vector point ) {
    vec2D A = createVec2D(    a.getX(),     a.getZ());
    vec2D B = createVec2D(    b.getX(),     b.getZ());
    vec2D C = createVec2D(    c.getX(),     c.getZ());
    vec2D m = createVec2D(point.getX(), point.getZ());

    vec2D AB = vectorise(A, B);
    vec2D AM = vectorise(A, m);
    vec2D AC = vectorise(A, C);
    double dotABAM = dot(AB, AM);
    double dotABAB = dot(AB, AB);
    double dotAMAC = dot(AM, AC);
    double dotACAC = dot(AC, AC);
    return (0 <= dotABAM && dotABAM <= dotABAB && 0 <= dotAMAC && dotAMAC <= dotACAC);
}

std::string checkIfInsideWall(int i, Vector point, const Box& b) {
    switch (i) {
        case 0:
            //std::cout<<"YZ abcd\n";
            if(pointInRectangleYZ( b.a, b.b, b.c, point))
                return "0";
            else
                return ".";
        case 1:
            ////GOOD
            if(pointInRectangleXZ( b.a, b.b, b.e, point))
                return "1";
            else
                return ".";
        case 2:
            //std::cout<<"YZ efgh\n";
            if(pointInRectangleYZ( b.e, b.f, b.g, point))
                return "2";
            else
                return ".";
        case 3:
            ////GOOD
            if(pointInRectangleXZ( b.d, b.g, b.h, point))
                return "3";
            else
                return ".";
        case 4:
            //std::cout<<"XY aceg\n";
            if(pointInRectangleXY( b.c, b.g, b.a, point))
                return "4";
            else
                return ".";
        case 5:
            //std::cout<<"XY bdfh\n";
            if(pointInRectangleXY( b.b, b.d, b.f, point))
                return "5";
            else
                return ".";
        default:
            return ".";
    }
}

std::string collidesWithBox(const Box& b, const Line& l) {
    Vector test = Vector(0,0,0);
    std::string temp = "";
    for (int i=0; i<6; i++) {
        test = calculateIntersectionLinePlane(l, b.planes.at(i));
        if(!test.equals(Vector(2137,2137,2137))) {
             temp = checkIfInsideWall(i, test, b);
            if( temp != ".") {

                return temp;
            }
        }
    }
    //std::cout<<"kiedys sie wykonalem";
    return ".";

}


Vector calculateIntersectionSectionSection(const Section& s1, const Section& s2);
Vector calculateIntersectionSectionSection(const Section& s1, const Section& s2);
Vector calculateIntersectionLineLine(const Line& l1, const Line& l2);
Line calculateLineBetweenPlanes(const Plane& p1, const Plane& p2, double a1 = 2, double b1 = -1, double c1 =  1, double d1 = -8, double a2 = 4, double b2 = 3, double c2 = 1, double d2 = 14);
void calculateIntersectionSphereLine(const Line& l, const Sphere& s);

Box rotateBox(Box box, double angle, const Vector& axis) {
    Vector a = Quaternion::rotate(box.a, angle, axis);
    Vector b = Quaternion::rotate(box.b, angle, axis);
    Vector c = Quaternion::rotate(box.c, angle, axis);
    Vector d = Quaternion::rotate(box.d, angle, axis);
    Vector e = Quaternion::rotate(box.e, angle, axis);
    Vector f = Quaternion::rotate(box.f, angle, axis);
    Vector g = Quaternion::rotate(box.g, angle, axis);
    Vector h = Quaternion::rotate(box.h, angle, axis);
    Plane acd = createPlane(a, c, d);
    Plane abe = createPlane(a, b, e);
    Plane efh = createPlane(e, f, h);
    Plane cgh = createPlane(c, g, h);
    Plane ace = createPlane(a, c, e);
    Plane bdf = createPlane(b, d, f);
    std::vector <Plane> planes;
    planes.push_back(acd);
    planes.push_back(abe);
    planes.push_back(efh);
    planes.push_back(cgh);
    planes.push_back(ace);
    planes.push_back(bdf);
    return {a,b,c,d,e,f,g,h,planes};
}



int main() {
    Box box = createBox(Vector(15,15,15), Vector(15,15,-15),
                        Vector(15,-15,15), Vector(15,-15,-15),
                        Vector(-15,15,15), Vector(-15,15,-15),
                        Vector(-15,-15,15), Vector(-15,-15,-15));
    Box box1 = rotateBox(box, 45, Vector(1,0,0));

    Box box2 = rotateBox(box, 90, Vector(0,1,0));
    //Line line = createLine(Vector(0,0,0), Vector(0,-15,0));
    Line lineArr[60][60];
    int y = 30;
    int z = 30;
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 60; j++) {
            lineArr[i][j] = createLine(Vector(-30,y,z), Vector(30,y,z));
            //std::cout<<"POINT x: "<<lineArr[i][j].point.getX()<<" y: "<<lineArr[i][j].point.getY()<<" z: "<<lineArr[i][j].point.getZ()<<"\n";
            //std::cout<<"VECTORx: "<<lineArr[i][j].vector.getX()<<" y: "<<lineArr[i][j].vector.getY()<<" z: "<<lineArr[i][j].vector.getZ()<<"\n";
            y--;
        }
        y = 30;
        z--;
    }

    std::string resultArr[60][60];
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 60; j++) {
            resultArr[i][j] = collidesWithBox(box2, lineArr[i][j]);
        }
    }

    std::stringstream ss;
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 60; j++) {
            ss<<" " << resultArr[i][j];
        }
    }
    std::cout<<ss.str();

    return 0;
}

void task4() {
    //zad1
    Line line1 = createLine(Vector(-2,4,0), Vector(1,5,5));
    Line line2 = createLine(Vector(-2,4,0), Vector(-1,-1,3));

    printf("zad1 point: %s", calculateIntersectionLineLine(line1, line2).str().c_str());

    //zad2
    double angle = line1.vector.findAngle(line2.vector);
    printf("\nzad2 angle: %f", angle);

    //zad3
    Line line3 = createLine(Vector(-2,2,-1), Vector(1,1,1));
    Plane plane1 = createPlane(Vector(4,0,0), Vector(1,0,2), Vector(1,2,0));
    printf("\n\nzad3 point: %s", calculateIntersectionLinePlane(line3, plane1).str().c_str());

    //zad4
    double angle2 = line3.vector.findAngle(plane1.normal);
    printf("\nzad4 angle: %f", angle2);

    //zad5
    Plane plane2 = createPlane(Vector(4,0,0), Vector(0,-8,0), Vector(0,0,8));
    Plane plane3 = createPlane(Vector(0,0,-14), Vector(0,-3,-5), Vector(-3,0,-2));
    printf("\n\nzad5");
    Line intersectionLine = calculateLineBetweenPlanes(plane2, plane3, 2, -1, 1, -8, 4, 3, 1, 14); //
    printf(" found line: %s + t%s", intersectionLine.point.str().c_str(), intersectionLine.vector.normalise().str().c_str());


    //zad6
    double angle3 = plane2.normal.findAngle(plane3.normal);
    printf("\nzad6 angle: %f", angle3);

    //zad7
    Section section1 = {Vector(5,5,4), Vector(10,10,6)};
    Section section2 = {Vector(5,5,5), Vector(10,10,3)};
    printf("\n\nzad 7 point: %s", calculateIntersectionSectionSection(section1, section2).str().c_str());

    //zad8
    Line line4 = createLine(Vector(5,3,-4),Vector(3,-1,-2));
    Sphere sphere1 = {Vector(0,0,0), sqrt(26)};
    calculateIntersectionSphereLine(line4, sphere1);
}


double calculateTLineLine(Line l1, Line l2) {
    Vector p1 = l1.point;
    Vector p2 = l2.point;
    Vector v1 = l1.vector;
    Vector v2 = l2.vector;

    p2.sub(p1);
    Vector p2xv2 = p2.cross(v2);
    Vector v1xv2 = v1.cross(v2);
    double numerator = p2xv2.dot(v1xv2);
    double v1xv2len = pow(v1xv2.length(), 2);
    return numerator / v1xv2len;
}

Vector calculateIntersectionLineLine(const Line& l1, const Line& l2) {
    double t1 = calculateTLineLine(l1, l2);
    double t2 = calculateTLineLine(l2, l1);
    Vector p1 = l1.point;
    Vector v1 = l1.vector;
    Vector point1 = p1;

    point1.add(v1.multpily(t1));

    Vector point2 = l2.point;
    Vector v2 = l2.vector;
    point2.add(v2.multpily(t2));

    Vector n = point2;
    n.sub(point1);

    if(n.equals(Vector(0,0,0))){
        return point1;
    }

}

Vector calculateIntersectionSectionSection(const Section& s1, const Section& s2) {
    Line l1 = createLine(s1.A, s1.B);
    Line l2 = createLine(s2.A, s2.B);

    Vector p = calculateIntersectionLineLine(l1, l2);

    if( p.getX() >= s1.A.getX() && p.getX() <= s1.B.getX() &&
        p.getY() >= s1.A.getY() && p.getY() <= s1.B.getY() &&
        p.getZ() >= s1.A.getZ() && p.getZ() <= s1.B.getZ() &&
        p.getX() >= s2.A.getX() && p.getX() <= s2.B.getX() &&
        p.getY() >= s2.A.getY() && p.getY() <= s2.B.getY() &&
        p.getZ() >= s2.A.getZ() && p.getZ() <= s2.B.getZ())
        return p;
}

Line calculateLineBetweenPlanes(const Plane& p1, const Plane& p2, double a1, double b1, double c1, double d1, double a2, double b2, double c2, double d2){
    Vector q1 = p1.point;
    Vector q2 = p2.point;
    Vector n1 = p1.normal;
    Vector n2 = p2.normal;

    Vector n3 = n1.cross(n2);

//    if(n3.cross(Vector(1,0,0)) == Vector(0,0,0))  {
//        if(n3.cross(Vector(0,0,1)) == Vector(0,0,0))  {
//            double y = 0;
//            double z = ((b2/b1)*d1 -d2)/(c2 - c1*b2/b1);
//            double x = (-c1*z -d1) / b1;
//        }
//    }
    double x = 0;
    double z = ((b2/b1)*d1 -d2)/(c2 - c1*b2/b1);
    double y = (-c1*z -d1) / b1;

    return {};

}

void calculateIntersectionSphereLine(const Line& l, const Sphere& s) {
    Vector v = l.vector;
    Vector e = l.point;
    Vector center = s.center;
    double r = s.radius;
    Vector e_c = e;
    e_c.sub(center);

    double a = pow(v.length(), 2);
    double b = 2 * e_c.dot(v);
    double c = pow(e_c.length(),2) - r*r;

    double delta = b * b - 4 * a * c;
    double t1, t2;

    if (delta > 0) {
        printf("\n\nzad8 there are two intersections");
        t1 = (-b + sqrt(delta)) / (2 * a);
        t2 = (-b - sqrt(delta)) / (2 * a);

        Vector point1 = l.point;
        Vector point2 = l.point;
        Vector vector = l.vector;
        point1.add(vector.multpily(t1));
        point2.add(vector.multpily(t2));

        printf("\npoint 1: %s", point1.str().c_str());
        printf("\npoint 2: %s", point2.str().c_str());
    }
    else if(delta == 0) {
        printf("\n\nzad8 there is one intersection");
        t1 = -b/(2*a);
        Vector point = l.point;
        Vector vector = l.vector;

        point.add(vector.multpily(t1));
        printf("\npoint 1: %s", point.str().c_str());
    }
    else {
        printf("\n\nzad8 there are no intersections");
    }
}


void task1() {
        std::string vec;
    ////sprawdzenie przemiennosci
    Vector v1 = Vector(5,4,3);
    Vector v1c = v1.copy();
    Vector v2 = Vector(1,2,3);
    v1.add(v2);
    printf("%s + %s = %s\n", v1c.str().c_str(), v2.str().c_str(), v1.str().c_str());

    Vector v3 = Vector(5,4,3);
    Vector v4 = Vector(1,2,3);
    v4.add(v3);
    printf("%s + %s = %s \n", v2.str().c_str(), v1c.str().c_str(), v4.str().c_str());


    if(v1.equals(v4)) {
        printf("Dodawanie jest przemienne \n");
    }
    else {
        printf("Dodawanie niejest przemienne \n");
    }
    printf("\n");

    ////obliczanie kąta
    Vector v5 = Vector(0,3,0);
    Vector v6 = Vector(5,5,0);
    printf("kat miedzy wektorami %s i %s (w stopniach): \n%f \n", v5.str().c_str(), v6.str().c_str(), v5.findAngle(v6));
    printf("\n");

    ////wektor prostopadły
    Vector v7 = Vector(4,5,1);
    Vector v8 = Vector(4,1,3);
    Vector perp = v7.cross(v8);
    printf("wektor prostopadly do %s i %s: \n%s \n", v7.str().c_str(), v8.str().c_str(), perp.str().c_str());
    printf("\n");

    printf("%s dot %s = %f \n", v7.str().c_str(), perp.str().c_str(), v7.dot(perp));
    printf("%s dot %s = %f \n", v8.str().c_str(), perp.str().c_str(), v8.dot(perp));
    printf("\n");

    ////normalizacja wektora
    Vector normalised = perp.normalise();
    printf("wektor %s znormalizowany: %s \n", perp.str().c_str(), normalised.str().c_str());
    printf("dlugosc wektora znormalizowanego: %f \n", normalised.length());
}

void task2() {
        double values[16] = {0,1,2,3,
                        4,5,6,7,
                        8,9,10,11,
                        12,13,14,15};
    double values2[16] = {1,2,1,2,
                          1,2,1,2,
                          1,2,1,2,
                          1,2,1,2};
    ////dodawanie, odejmowanie, mnozenie przez skalar
    Matrix m1 = Matrix(values);
    printf("matrix D: \n%s", m1.str().c_str());
    m1.add(Matrix(values));
    printf("\nmatrix D + D: \n%s", m1.str().c_str());
    Matrix m2 = Matrix(values);
    m2.sub(Matrix(values));
    printf("\nmatrix D - D: \n%s", m2.str().c_str());
    Matrix m3 = m1.multpily(4);
    printf("\nmatrix D * 4: \n%s", m3.str().c_str());

    ////sprawdzenie przemiennosci mnozenia
    Matrix A = Matrix(values);
    printf("\n\nmatrix A: \n%s", A.str().c_str());
    Matrix B = Matrix(values2);
    printf("\nmatrix B: \n%s", B.str().c_str());
    Matrix resultAB = A.multiplyByMatrix(B);
    Matrix resultBA = B.multiplyByMatrix(A);
    printf("\nmatrix A*B: \n%s", resultAB.str().c_str());
    printf("\nmatrix B*A: \n%s", resultBA.str().c_str());
    if(resultAB.equals(resultBA))
        printf("\nMnozenie jest przemienne \n");
    else
        printf("\nMnozenie nie jest przemienne \n");

    ////transpozycja
    Matrix transpose = resultBA.transpose();
    printf("\nmatrix B*A transposed: \n%s", transpose.str().c_str());

    ////macierz jednostkowa
    transpose.readyIdentity();
    printf("\nidentity matrix: \n%s", transpose.str().c_str());

    ////wyznacznik
    double niceDetValues[16] = {1,1,-1,1,
                               2,2,-2,1,
                               -2,4,-2,-2,
                               2,-2,2,6};
    Matrix matrix = Matrix(niceDetValues);
    printf("\n\nmatrix C: \n%s", matrix.str().c_str());
    printf("\ndet(C) = %f", matrix.getDeterminant());

    ////macierz odwrotna
    Matrix inversed = matrix.inverse();
    printf("\n\n(c)^-1: \n%s", inversed.str().c_str());

    ////translacja
    Vector v1 = Vector(5,4,3, 1);
    Matrix operation = Matrix(niceDetValues);
    operation.readyTranslation(v1);
    printf("\n\noperation vector: %s \noperation matrix: \n%s", v1.str().c_str(), operation.str().c_str());

    ////skalowanie
    operation.readyScale(v1);
    printf("\nscale matrix: \n%s", operation.str().c_str());

    ////obroty
    Vector v2 = Vector(2,1,3, 1);
    operation.readyRotationAxis(v2, 90);
    printf("\n\nrotation vector: %s\nrotation angle = 90 \nrotation matrix: \n%s", v1.str().c_str(), operation.str().c_str());
    operation.readyRotationX(90);
    printf("\nrotation (X, 90) matrix: \n%s", operation.str().c_str());
    operation.readyRotationY(90);
    printf("\nrotation (Y, 90) matrix: \n%s", operation.str().c_str());
    operation.readyRotationZ(90);
    printf("\nrotation (Z, 90) matrix: \n%s", operation.str().c_str());

}

void task3() {
        ////zad3
    double niceDetValues[16] = {5,4,3,1,
                                -2,6,-9,1,
                                8,2,1,1,
                                1,1,1,1};

    Vector vec = Vector(1,0,0,1);
    Matrix rotation = Matrix(niceDetValues);
    rotation.readyRotationY(90);
    Vector rotatedVec = rotation.multiplyByVector(vec);
    printf("\n\n%s rotated (Y, 90): %s", vec.str().c_str(), rotatedVec.str().c_str());
    Quaternion q1 = Quaternion(4, 1, 2, 3);
    printf("q1: \n%s", q1.str().c_str());
    Quaternion q1c = q1.copy();

    q1.add(q1c);
    printf("\n\nq2 = q1 + q1: \n%s", q1.str().c_str());

    q1c.sub(q1c);
    printf("\n\nq3 = q1 - q1: \n%s", q1c.str().c_str());

    Quaternion q4 = Quaternion(2, 5, 6, 7);
    printf("\n\nq4: \n%s", q4.str().c_str());
    Quaternion q5 = Quaternion(3, 2, 3, 4);
    printf("\nq5: \n%s", q5.str().c_str());

    Quaternion q6 = q4.mul(q5);
    printf("\n\nq6 = q4 * q5: \n%s", q6.str().c_str());
    Quaternion q7 = q5.mul(q4);
    printf("\nq7 = q5 * q4: \n%s", q7.str().c_str());
    printf("\nmnozenie kwaternionow%s jest przemienne", q6.equals(q7) ? "" : " nie");

    Quaternion q8 = q4.div(q5);
    printf("\n\nq8 = q4 / q5: \n%s", q8.str().c_str());

    Vector point = Vector(-1,-1,-1);
    Vector rotationAxis = Vector(1, 0, 0);
    double angle = 270;
    Quaternion q9 = Quaternion(0,0,0,0);
    q9.prepareQuaternion(angle, point);
    printf("\nrotation quaternion: \n%s", q9.str().c_str());
    q9.inverse();
    printf("\ninversed quaternion: \n%s", q9.str().c_str());

    Vector rotated = Quaternion::rotate(point, angle, rotationAxis);
    printf("\n\nrotated point: \n%s", rotated.str().c_str());
}

