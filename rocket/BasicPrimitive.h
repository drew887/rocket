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
        Matrix model;
    public:
        BasicPrimitive();
        virtual ~BasicPrimitive();
        virtual void Render() = 0;
        virtual void Translate(Vector npos);
        virtual void Translate(float amountX, float amountY, float amountZ);
        virtual void setTranslate(Vector npos);
        virtual void setTranslate(float amountX, float amountY, float amountZ);
        virtual void Rotate(float deg, float amountX, float amountY, float amountZ);
        virtual void Scale(float amountX, float amountY, float amountZ);

        int modelLoc;
        Vector position;
    };
}
#endif