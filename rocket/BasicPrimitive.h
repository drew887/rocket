#pragma once
#ifndef ANGL_BASICPRIMITIVE_H
#define ANGL_BASICPRIMITIVE_H

#include "Matrix.h"
#include "Vector.h"

namespace anGL {
    class BasicPrimitive {
    protected:
        float * verticies;
        unsigned int vertexBufferID, vertexArrayID;
    public:
        BasicPrimitive();
        virtual ~BasicPrimitive();
        virtual void Render() = 0;
        virtual void Translate(Vector npos);
        virtual void Translate(float amountX, float amountY, float amountZ);
        virtual void Rotate(float deg, float amountX, float amountY, float amountZ);
        virtual void Scale(float amountX, float amountY, float amountZ);

        Matrix model;
        int modelLoc;
        Vector position;
    };
}
#endif