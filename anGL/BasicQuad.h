#pragma once
#ifndef ANGL_BASICQUAD_H
#define ANGL_BASICQUAD_H
#include "Texture.h"
#include "BasicPrimitive.h"

namespace anGL {
    //! A basic texturable quad
    class BasicQuad : public BasicPrimitive {
    protected:
        unsigned int texCoordBufferID;
    public:
        BasicQuad(float width, float height);
        virtual ~BasicQuad();
        virtual void render();
        void setLocs(int programID);
        virtual Vector getDims(); //! returns a Vector representing the width, height, and depth of the Quad, as scaled by mScale.

        Texture texture;
        int sampleLoc;
    };
}

#endif