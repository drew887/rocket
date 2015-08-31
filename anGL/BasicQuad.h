#pragma once
#ifndef ANGL_BASICQUAD_H
#define ANGL_BASICQUAD_H
#include "Texture.h"
#include "BasicPrimitive.h"

namespace anGL {
    class BasicQuad : public BasicPrimitive {
    protected:
        unsigned int texCoordBufferID;
    public:
        BasicQuad(float width, float height);
        virtual ~BasicQuad();
        virtual void render();
        void setLocs(int programID);
        Texture texture;
        int sampleLoc;
    };
}

#endif