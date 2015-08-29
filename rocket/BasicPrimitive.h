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
        Matrix model, mRotation, mScale, mTranslation;
    public:
        BasicPrimitive();
        virtual ~BasicPrimitive();
        virtual void render() = 0;
        virtual void update();
        virtual void translate(Vector npos);
        virtual void translate(float amountX, float amountY, float amountZ);
        virtual void setTranslate(Vector npos);
        virtual void setTranslate(float amountX, float amountY, float amountZ);
        virtual void rotate(float deg, float amountX, float amountY, float amountZ);
        virtual void setRotate(float deg, float amountX, float amountY, float amountZ);
        virtual void scale(float amountX, float amountY, float amountZ);
        virtual void setScale(float amountX, float amountY, float amountZ);
        int modelLoc;
        Vector position;
    };
}
#endif