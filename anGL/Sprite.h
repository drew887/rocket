#pragma once
#ifndef ANGL_SPRITE_H
#define ANGL_SPRITE_H

#include <gl\glew.h>

#include "BasicQuad.h"
#include "Texture.h"
#include "Vector.h"

namespace anGL {
    class Sprite : public BasicQuad {
    public:
        Sprite(float width, float height);
        virtual ~Sprite();

        Image spriteSheet;
    };
}
#endif