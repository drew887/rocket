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
        BasicQuad(float width, float height,  int uniformLoc = -1);
        virtual ~BasicQuad();
        virtual void Render();
        Texture texture;
        int sampleLoc;
    };
}

#endif