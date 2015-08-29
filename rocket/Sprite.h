#pragma once
#ifndef ANGL_SPRITE_H
#define ANGL_SPRITE_H

#include <gl\glew.h>

#include "BasicPrimitive.h"
#include "Texture.h"
#include "Vector.h"

namespace anGL {
    class Sprite : public BasicPrimitive {
    protected:
        unsigned int texCoordBufferID;
    public:
        Sprite(float width, float height);
        virtual ~Sprite();
        virtual void render();
        Texture texture;
        BMP spriteSheet;
        float width, height;
        Vector getDims();
    };
}
#endif