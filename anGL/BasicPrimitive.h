/*----------------------------------------------*\
|                                                |
|                 BasicPrimitive.h               |
| BasicPrimitive is an abstract class providing  |
| utility for the shape classes that are its     |
| children.                                      |
|                                                |
| Children are required to define the render and |
| getDims functions as that will be unique to    |
| each shape.                                    |
|                                                |
| The verticies member is intended to be a       |
| pointer to an array of floats representing the |
| coordinates of the shape. It is up to the      |
| child's constructor to allocate the memory but |
| the BasicPrimitive destructor will delete the  |
| array.                                         |
|                                                |
| This class also holds ids for a VBO and a VAO  |
| which are created and destroyed in this class, |
| no need to do so in the child classes.         |
\*----------------------------------------------*/
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
        float width, height, depth;
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
        virtual Vector getDims() = 0;
        int modelLoc;
        Vector position;
    };
}
#endif