#include "Vector.h"

using namespace anGL;

Vector::Vector(float X, float Y, float Z, float W): x(points[0]), y(points[1]), z(points[2]), w(points[3]){
    x = X;
    y = Y;
    z = Z;
    w = W;
}

anGL::Vector::Vector(const Vector & other) : x(points[0]), y(points[1]), z(points[2]), w(points[3]) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
}

Vector::~Vector(){

}
////        ////
// Vector ops //
////        ////
Vector& Vector::operator=(const Vector & other) {
    for(int ctr = 0; ctr < 4; ctr++) {
        points[ctr] = other.points[ctr];
    }
    return *this;
}

Vector Vector::operator+(const Vector & other) {
    Vector result;
    result.x = (x + other.x);
    result.y = (y + other.y);
    result.z = (z + other.z);
    result.w = (w + other.w);
    return result;
}

Vector& Vector::operator+=(const Vector & other) {
    *this = *this + other;
    return *this;
}

Vector anGL::Vector::operator-(const Vector & other) {
    Vector result;
    result.x = (x - other.x);
    result.y = (y - other.y);
    result.z = (z - other.z);
    result.w = (w - other.w);
    return result;
}

Vector& anGL::Vector::operator-=(const Vector & other) {
    *this = *this - other;
    return *this;
}

Vector anGL::Vector::operator*(const Vector & other) {
    Vector result;
    result.x = (x * other.x);
    result.y = (y * other.y);
    result.z = (z * other.z);
    result.w = (w * other.w);
    return result;
}

Vector& anGL::Vector::operator*=(const Vector & other) {
    *this = *this * other;
    return *this;
}

Vector anGL::Vector::operator/(const Vector & other) {
    Vector result;
    result.x = (x / other.x);
    result.y = (y / other.y);
    result.z = (z / other.z);
    result.w = (w / other.w);
    return result;
}

Vector& anGL::Vector::operator/=(const Vector & other) {
    *this = *this / other;
    return *this;
}
////        ////
// Scalar ops //
////        ////
Vector Vector::operator+(float rhs) {
    Vector result;
    result.x = (x + rhs);
    result.y = (y + rhs);
    result.z = (z + rhs);
    result.w = (w + rhs);
    return result;
}

Vector& Vector::operator+=(float rhs) {
    *this = *this + rhs;
    return *this;
}

Vector anGL::Vector::operator-(float rhs) {
    Vector result;
    result.x = (x - rhs);
    result.y = (y - rhs);
    result.z = (z - rhs);
    result.w = (w - rhs);
    return result;
}

Vector& anGL::Vector::operator-=(float rhs) {
    *this = *this - rhs;
    return *this;
}

Vector anGL::Vector::operator*(float rhs) {
    Vector result;
    result.x = (x * rhs);
    result.y = (y * rhs);
    result.z = (z * rhs);
    result.w = (w * rhs);
    return result;
}

Vector& anGL::Vector::operator*=(float rhs) {
    *this = *this * rhs;
    return *this;
}

Vector anGL::Vector::operator/(float rhs) {
    Vector result;
    result.x = (x / rhs);
    result.y = (y / rhs);
    result.z = (z / rhs);
    result.w = (w / rhs);
    return result;
}

Vector& anGL::Vector::operator/=(float rhs) {
    *this = *this / rhs;
    return *this;
}

////
float anGL::Vector::dot(const Vector other) const {
    float result = 0;
    result = (x*other.x) + (y*other.y) + (z*other.z);
    return result;
}

float anGL::Vector::dot4(const Vector other) const {
    float result = 0;
    result = (x*other.x) + (y*other.y) + (z*other.z) +(w*other.w);
    return result;
}

Vector anGL::Vector::cross(const Vector other) const {
    Vector result(0, 0, 0, 0);
    result.points[0] = (y*other.z) - (z*other.y);
    result.points[1] = (z*other.x) - (x*other.z);
    result.points[2] = (x*other.y) - (y*other.x);
    return result;
}

float anGL::dot(const Vector one, const Vector two, bool dot4) {
    if(dot4) {
        return one.dot4(two);
    }
    else {
        return one.dot(two);
    }
}

Vector anGL::cross(const Vector one, const Vector two){
    return one.cross(two);
}
