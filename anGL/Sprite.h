#pragma once
#ifndef ANGL_SPRITE_H
#define ANGL_SPRITE_H

#include <gl\glew.h>

#include "BasicPrimitive.h"
#include "Texture.h"
#include "Vector.h"

namespace anGL {
    //! A representation of a square 2D Sprite
    class Sprite : public BasicPrimitive {
    protected:
        unsigned int texCoordBufferID;
    public:
        Sprite(float width, float height);
        virtual ~Sprite();
        virtual void render();

        Texture texture; //! The texture to be rendered in the square of our Sprite
        Image spriteSheet; //! An Image representing a set of animation images for the Sprite
        float width, height;
        virtual Vector getDims(); //! returns a Vector representing the width, height, and depth of the Sprite, as scaled by mScale: (width, height, 0, 1) * mScale;
    };
}
#endif