#pragma once
#ifndef ANGL_MATRIX_H
#define ANGL_MATRIX_H

namespace anGL {
    //! a class for handling matricies!
    class Matrix {
    public:
        Matrix(float identity = 1);
        virtual ~Matrix();
        Matrix(const Matrix& other);
        Matrix& operator=(const Matrix& other);
        Matrix operator*(const Matrix& other);
        Matrix& operator*=(const Matrix& other);
        float& operator[](unsigned int offset);
        
        void setIdentity(float identity);
        //! Generates a perspective matrix, makes things look like they do in the real world
        void perspective(float fieldOfView, float aspect, float nearPlane, float farPlane);
        //! Generates a frustrum matrix, like the perspective one but without the eyeball effect
        void frustum(float top, float bottom, float left, float right, float nearPlane, float farPlane);
        //! Generates an orthographic matrix, basically removes the visual effect from depth
        void orthographic(float top, float bottom, float left, float right, float nearPlane, float farPlane);

        //! increases the rotation effect by rot amount by a ratio of each x y and z 
        void rotate(float rot, float x, float y, float z);
        //! inceases the scaling effect by x y z on their namesakes direction
        void scale(float x, float y, float z);
        //! inceases the translating effect x y z on their namesakes direction
        void translate(float x, float y, float z);

        //! sets up the matrix so that coordinates multiplied against it rotate
        void setRotation(float rot, float x, float y, float z);
        //! sets up the matrix so that coordinates multiplied against it translate
        void setTranslation(float x, float y, float z);
        //! sets up the matrix so that coordinates multiplied against it scale by x y z amount
        void setScale(float x, float y, float z);

        float * matrix;
    protected:
        //! just used for copying one matrix into another
        virtual void copy(const Matrix& o);
    };

    //! converts deg into radians
    float degtorad(float deg);
    //! converts rad into degrees
    float radtodeg(float rad);
}
#endif // ANGL_MATRIX_H
