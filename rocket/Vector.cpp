#include "Vector.h"
#include "Matrix.h"
#include <math.h>

using namespace anGL;

Vector::Vector(float X, float Y, float Z, float W): x(points[0]), y(points[1]), z(points[2]), w(points[3]){
    x = X;
    y = Y;
    z = Z;
    w = W;
}

Vector::Vector(const Vector & other) : x(points[0]), y(points[1]), z(points[2]), w(points[3]) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
}

Vector::~Vector(){

}

Vector Vector::operator*(const Matrix & other) {
    Vector result;
    float * m = other.matrix;
    result.x = (m[0] * x) + (m[1] * y) + (m[2] * z) + (m[3] * w);
    result.y = (m[4] * x) + (m[5] * y) + (m[6] * z) + (m[7] * w);
    result.z = (m[8] * x) + (m[9] * y) + (m[10] * z) + (m[11] * w);
    result.w = (m[12] * x) + (m[13] * y) + (m[14] * z) + (m[15] * w);
    return result;
}

Vector& Vector::operator*=(const Matrix & other) {
    *this = *this * other;
    return *this;
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

Vector Vector::operator-(const Vector & other) {
    Vector result;
    result.x = (x - other.x);
    result.y = (y - other.y);
    result.z = (z - other.z);
    result.w = (w - other.w);
    return result;
}

Vector& Vector::operator-=(const Vector & other) {
    *this = *this - other;
    return *this;
}

Vector Vector::operator*(const Vector & other) {
    Vector result;
    result.x = (x * other.x);
    result.y = (y * other.y);
    result.z = (z * other.z);
    result.w = (w * other.w);
    return result;
}

Vector& Vector::operator*=(const Vector & other) {
    *this = *this * other;
    return *this;
}

Vector Vector::operator/(const Vector & other) {
    Vector result;
    result.x = (x / other.x);
    result.y = (y / other.y);
    result.z = (z / other.z);
    result.w = (w / other.w);
    return result;
}

Vector& Vector::operator/=(const Vector & other) {
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

Vector Vector::operator-(float rhs) {
    Vector result;
    result.x = (x - rhs);
    result.y = (y - rhs);
    result.z = (z - rhs);
    result.w = (w - rhs);
    return result;
}

Vector& Vector::operator-=(float rhs) {
    *this = *this - rhs;
    return *this;
}

Vector Vector::operator*(float rhs) {
    Vector result;
    result.x = (x * rhs);
    result.y = (y * rhs);
    result.z = (z * rhs);
    result.w = (w * rhs);
    return result;
}

Vector& Vector::operator*=(float rhs) {
    *this = *this * rhs;
    return *this;
}

Vector Vector::operator/(float rhs) {
    Vector result;
    result.x = (x / rhs);
    result.y = (y / rhs);
    result.z = (z / rhs);
    result.w = (w / rhs);
    return result;
}

Vector& Vector::operator/=(float rhs) {
    *this = *this / rhs;
    return *this;
}

////
float Vector::dot(const Vector other) const {
    float result = 0;
    result = (x*other.x) + (y*other.y) + (z*other.z);
    return result;
}

float Vector::dot4(const Vector other) const {
    float result;
    result = (x*other.x) + (y*other.y) + (z*other.z) +(w*other.w);
    return result;
}

Vector Vector::cross(const Vector other) const {
    Vector result(0, 0, 0, 0);
    result.points[0] = (y*other.z) - (z*other.y);
    result.points[1] = (z*other.x) - (x*other.z);
    result.points[2] = (x*other.y) - (y*other.x);
    return result;
}

void Vector::normalize(){
    float mag = magnitude();
    x /= mag;
    y /= mag;
    z /= mag;
    w /= mag;
}

float Vector::magnitude() {
    return sqrtf((x*x) + (y*y) + (z*z) + (w*w));
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
