#pragma once
#ifndef ANGL_BASICQUAD_H
#define ANGL_BASICQUAD_H
#include "Matrix.h"
#include "Texture.h"
namespace anGL {
    class BasicQuad {
    protected:
        float * verticies;
        unsigned int vertexBufferID, texCoordBufferID, vertexArrayID;
    public:
        BasicQuad(float width, float height,  int uniformLoc = -1);
        virtual ~BasicQuad();
        virtual void Render();
        Matrix model, trans, rot, scale;
        Texture texture;
        int modelLoc, sampleLoc;
    };
}

#endif