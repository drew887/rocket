#pragma once
#ifndef ANGL_BASICPRIMITIVE_H
#define ANGL_BASICPRIMITIVE_H

#include "Matrix.h"
#include "Vector.h"

namespace anGL {
    //! A virtual class representing common functions for primitives
    class BasicPrimitive {
    protected:
        float * verticies; //! an array of verticies, initialized in child classes, but will be deleted in this destructor
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
        //! returns a Vector representing the width, height, and depth of the Primitive, must be implemented by child classes
        virtual Vector getDims() = 0;
        int modelLoc;
        Vector position; //! Updated when calling translate and setTranslate to show an xyz location, offset from origin
        float width, height;
    };
}
#endif