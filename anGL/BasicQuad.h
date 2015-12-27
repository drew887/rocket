/*----------------------------------------------*\
|                                                |
|                  BasicQuad.h                   |
| BasicQuad is a child class of BasicPrimitive   |
| that is supposed to represent a simple square  |
| centered around the origin with a texture.     |
\*----------------------------------------------*/
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
        virtual Vector getDims();

        Texture texture;
    };
}

#endif