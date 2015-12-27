/*--------------------------------------------*\
|                                              |
|                   Vector.h                   |
| A simple vector class. Not high level physics|
| compatible, but suits small 3d apps          |
\*--------------------------------------------*/
#pragma once
#ifndef ANGL_VECTOR_H
#define ANGL_VECTOR_H

namespace anGL {
    class Matrix;

    class Vector{

    public:
        Vector(float X = 0., float Y = 0., float Z = 0., float W = 1.);
        Vector(const Vector& other);
        ~Vector();

        Vector operator*(const Matrix& other);
        Vector& operator*=(const Matrix& other);

        //vector ops
        Vector& operator=(const Vector& other);
        Vector operator+(const Vector& other);
        Vector& operator+=(const Vector& other);
        Vector operator-(const Vector& other);
        Vector& operator-=(const Vector& other);
        Vector operator*(const Vector& other);
        Vector& operator*=(const Vector& other);
        Vector operator/(const Vector& other);
        Vector& operator/=(const Vector& other);

        //scalar ops
        Vector operator+(float rhs);
        Vector& operator+=(float rhs);
        Vector operator-(float rhs);
        Vector& operator-=(float rhs);
        Vector operator*(float rhs);
        Vector& operator*=(float rhs);
        Vector operator/(float rhs);
        Vector& operator/=(float rhs);

        float dot(const Vector other) const; //dot product as if a 3 point vector
        float dot4(const Vector other) const; //full 4 point dot product
        Vector cross(const Vector other) const;
        void normalize();
        float magnitude();

        float points[4];
        float &x, &y, &z, &w;

    };

    float dot(const Vector one, const Vector two, bool dot4 = false);
    Vector cross(const Vector one, const Vector two);
}
#endif