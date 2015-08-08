#pragma once
#ifndef ANGL_MATRIX_H
#define ANGL_MATRIX_H


//! a class for handling matricies!
namespace anGL {

    class Matrix {
    public:
        Matrix(float identity = 1);
        virtual ~Matrix();
        Matrix(const Matrix& other);
        Matrix& operator=(const Matrix& other);
        Matrix operator*(const Matrix& other);
        Matrix& operator*=(const Matrix& other);
        float& operator[](unsigned int offset);
        
        void perspective(float fieldOfView, float aspect, float nearPlane, float farPlane);
        void frustum(float top, float bottom, float left, float right, float nearPlane, float farPlane);
        void orthographic(float top, float bottom, float left, float right, float nearPlane, float farPlane);

        void scale(float x, float y, float z);
        void translate(float x, float y, float z);
        void rotate(float rot, float x, float y, float z);

        float * matrix;
    protected:
        void copy(const Matrix& o);
    };

    float degtorad(float deg);
    float radtodeg(float rad);
}
#endif // ANGL_MATRIX_H