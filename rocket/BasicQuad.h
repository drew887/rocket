#pragma once
#ifndef ANGL_BASICQUAD_H
#define ANGL_BASICQUAD_H
#include "Matrix.h"
namespace anGL {
    class BasicQuad {
    protected:
        float * verticies;
        unsigned int bufferID, vertexArrayID;
    public:
        BasicQuad(float width, float height, float startX = 0.f, float startY = 0.f, int uniformLoc = -1);
        virtual ~BasicQuad();
        virtual void Render();
        Matrix model, trans, rot, scale;
        int modelLoc;
    };
}

#endif