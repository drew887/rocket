#include "Matrix.h"

using namespace anGL;

/*!
    \param identity number to set the base identity of the matrix to, by default 1.0f
    note that the regular matrix looks like: (if i is identity)\n
    i 0 0 0\n
    0 i 0 0\n
    0 0 i 0\n
    0 0 0 i
*/
Matrix::Matrix(float identity) {
    matrix = new float[16];
    for(int i = 0; i < 16; i++) matrix[i] = 0;
    matrix[0] = identity;
    matrix[5] = identity;
    matrix[10] = identity;
    matrix[15] = identity;
}

Matrix::~Matrix() {
    delete[] matrix;
}

void Matrix::copy(const Matrix& o) {
    for(int i = 0; i < 16; i++) {
        this->matrix[i] = o.matrix[i];
    }
}

Matrix::Matrix(const Matrix& other) {
    matrix = new float[16];
    this->copy(other);
}

Matrix& Matrix::operator=(const Matrix& rhs) {
    if(this == &rhs) return *this; // handle self assignment
    this->copy(rhs);
    return *this;
}

Matrix Matrix::operator*(const Matrix& o) {
    float * m = matrix;
    float * p = o.matrix;
    Matrix result;
    //first row
    result[0] = ((m[0] * p[0]) + (m[1] * p[4]) + (m[2] * p[8]) + (m[3] * p[12]));
    result[1] = ((m[0] * p[1]) + (m[1] * p[5]) + (m[2] * p[9]) + (m[3] * p[13]));
    result[2] = ((m[0] * p[2]) + (m[1] * p[6]) + (m[2] * p[10]) + (m[3] * p[14]));
    result[3] = ((m[0] * p[3]) + (m[1] * p[7]) + (m[2] * p[11]) + (m[3] * p[15]));
    //second row
    result[4] = ((m[4] * p[0]) + (m[5] * p[4]) + (m[6] * p[8]) + (m[7] * p[12]));
    result[5] = ((m[4] * p[1]) + (m[5] * p[5]) + (m[6] * p[9]) + (m[7] * p[13]));
    result[6] = ((m[4] * p[2]) + (m[5] * p[6]) + (m[6] * p[10]) + (m[7] * p[14]));
    result[7] = ((m[4] * p[3]) + (m[5] * p[7]) + (m[6] * p[11]) + (m[7] * p[15]));
    //third
    result[8] = ((m[8] * p[0]) + (m[9] * p[4]) + (m[10] * p[8]) + (m[11] * p[12]));
    result[9] = ((m[8] * p[1]) + (m[9] * p[5]) + (m[10] * p[9]) + (m[11] * p[13]));
    result[10] = ((m[8] * p[2]) + (m[9] * p[6]) + (m[10] * p[10]) + (m[11] * p[14]));
    result[11] = ((m[8] * p[3]) + (m[9] * p[7]) + (m[10] * p[11]) + (m[11] * p[15]));
    //forth
    result[12] = ((m[12] * p[0]) + (m[13] * p[4]) + (m[14] * p[8]) + (m[15] * p[12]));
    result[13] = ((m[12] * p[1]) + (m[13] * p[5]) + (m[14] * p[9]) + (m[15] * p[13]));
    result[14] = ((m[12] * p[2]) + (m[13] * p[6]) + (m[14] * p[10]) + (m[15] * p[14]));
    result[15] = ((m[12] * p[3]) + (m[13] * p[7]) + (m[14] * p[11]) + (m[15] * p[15]));
    return result;
}

Matrix& Matrix::operator*=(const Matrix& o) {
    *this = *this * o;
    return *this;
}

float& Matrix::operator[](unsigned int offset) {
    if(offset > 15) { offset = 15; }
    return matrix[offset];
}

#include <math.h>
#define PI 3.14159265f
float anGL::degtorad(float deg) {
    return deg * (PI / 180);
}
float anGL::radtodeg(float rad) {
    return rad * (180 / PI);
}

////        ////
// View funcs //
////        ////
/*!
    \param fieldOfView a float representing how large to have the field of view, smaller numbers will have a zoom in effect
    \param aspect a float representing the aspect ratio of the perspective, normally you want this to be your window width / height
    \param near where the near clipping plane is
    \param far where to stick the far clipping plane
*/
void Matrix::perspective(float fieldOfView, float aspect, float near, float far) {
    float tanOfView = tanf(fieldOfView / 2.0f);
    matrix[0] = 1 / (aspect * tanOfView);
    matrix[5] = 1 / (tanOfView);
    matrix[10] = -(far + near) / (far - near);
    matrix[11] = -1;                            //-1 for righthanded coordinates
    matrix[14] = -2 * (far * near) / (far - near); //-2 for righthanded, switch these both positive to suddenly have left handed coordinates
    matrix[15] = 0;
}
/*!
    \param near defines the near clipping plane
    \param far defines the far clipping plane

    top, bottom, left, and right define the lengths of the 4 sides of the view. Defines a view matrix that allows for depth perception,
    although without a controlable field of view.
*/
void Matrix::frustum(float top, float bottom, float left, float right, float near, float far) {
    matrix[0] = (2 * near) / (right - left);
    matrix[5] = (2 * near) / (top - bottom);
    matrix[8] = (right + left) / (right - left);
    matrix[9] = (top + bottom) / (top - bottom);
    matrix[10] = -(far + near) / (far - near);
    matrix[11] = -1;
    matrix[14] = -2 * (far * near) / (far - near);
    matrix[15] = 0;
}
/*!
\param near defines the near clipping plane
\param far defines the far clipping plane

top, bottom, left, and right define the lengths of the 4 sides of the view. Defines a view matrix that doesn't allow for depth perception,
no matter the depth all objects appear as if at the same depth
*/
void Matrix::orthographic(float top, float bottom, float left, float right, float near, float far) {
    matrix[0] = 2 / (right - left);
    matrix[5] = 2 / (top - bottom);
    matrix[10] = -2 / (far - near);
    matrix[12] = -(right + left) / (right - left);
    matrix[13] = -(top + bottom) / (top - bottom);
    matrix[14] = -(far + near) / (far - near);
    matrix[15] = 1;
}

  ////                   ////
 // Transformation funcs  //
////                   ////

void Matrix::setScale(float x, float y, float z) {
    matrix[0] = x;
    matrix[5] = y;
    matrix[10] = z;
}

void Matrix::scale(float x, float y, float z) {
    Matrix temp;
    temp.matrix[0] += x;
    temp.matrix[5] += y;
    temp.matrix[10] += z;
    *this = temp * *this;
}

void Matrix::setTranslation(float x, float y, float z) {
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
}

void Matrix::translate(float x, float y, float z) {
    Matrix temp;
    matrix[12] += x;
    matrix[13] += y;
    matrix[14] += z;
    *this = temp * *this;
}

void Matrix::rotate(float rot, float rx, float ry, float rz) {
    float s, c, t;//sin cos and 1-cos constants
    float rad = degtorad(rot);
    s = sinf(rad);
    c = cosf(rad);
    t = 1 - cosf(rad);
    Matrix result;
    result.matrix[0] = (t * (rx*rx)) + c;//the diagonals
    result.matrix[5] = (t * (ry*ry)) + c;
    result.matrix[10] = (t * (rz*rz)) + c;
    //set up the xplane
    result.matrix[4] = (t * (rx*ry)) - (s*rz);
    result.matrix[8] = (t * (rx*rz)) + (s*ry);
    //set up the yplane
    result.matrix[1] = (t * (rx*ry)) + (s*rz);
    result.matrix[9] = (t * (ry*rz)) - (s*rx);
    //set up zplane
    result.matrix[2] = (t * (rx*rz)) - (s*ry);
    result.matrix[6] = (t * (ry*rz)) + (s*rx);
    *this = result * *this;
}

void Matrix::setRotation(float rot, float rx, float ry, float rz){
    float s, c, t;//sin cos and 1-cos constants
    float rad = degtorad(rot);
    s = sinf(rad);
    c = cosf(rad);
    t = 1 - cosf(rad);
    matrix[0] = (t * (rx*rx)) + c;//the diagonals
    matrix[5] = (t * (ry*ry)) + c;
    matrix[10] = (t * (rz*rz)) + c;
    //set up the xplane
    matrix[4] = (t * (rx*ry)) - (s*rz);
    matrix[8] = (t * (rx*rz)) + (s*ry);
    //set up the yplane
    matrix[1] = (t * (rx*ry)) + (s*rz);
    matrix[9] = (t * (ry*rz)) - (s*rx);
    //set up zplane
    matrix[2] = (t * (rx*rz)) - (s*ry);
    matrix[6] = (t * (ry*rz)) + (s*rx);
}
