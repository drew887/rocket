#pragma once
#ifndef ANGL_VECTOR_H
#define ANGL_VECTOR_H
namespace anGL {
    //!Represents a 4 point vector
    class Vector{

    public:
        Vector(float X = 0., float Y = 0., float Z = 0., float W = 1.);
        Vector(const Vector& other);
        ~Vector();

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

        //! returns the dot product as if it was only a 3 point vector
        float dot(const Vector other) const; //dot product as if a 3 point vector
        //! returns the full 4 point dot product
        float dot4(const Vector other) const; //full 4 point dot product
        //! returns the cross product of other and this as a direction, aka the w component is 0
        Vector cross(const Vector other) const;

        float points[4];
        float &x, &y, &z, &w;

    };
    //! If dot4 is true it returns as if one.dot4(two) otherwise returns one.dot(two)
    float dot(const Vector one, const Vector two, bool dot4 = false);
    //! returns one.cross(two)
    Vector cross(const Vector one, const Vector two);
}
#endif