#include "BasicQuad.h"
#include <GL/glew.h>
using namespace anGL;

BasicQuad::BasicQuad(float nWidth, float nHeight){
    nWidth /= 2;
    nHeight /= 2;
    verticies = new float[8]{
        -nWidth, -nHeight,
        nWidth, -nHeight,
        -nWidth, nHeight,
        nWidth, nHeight
    };
    width = nWidth;
    height = nHeight;
   float texts[] = { //reversed tex coords to adjust for how openGL UV coordinates work, rather than just flipping all our texture data
        0, 1,
        1, 1,
        0, 0,
        1, 0
    };

    int current = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current);
    glBindVertexArray(vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, verticies, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &texCoordBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, texts, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(current);
}

BasicQuad::~BasicQuad() {
    glDeleteBuffers(1, &texCoordBufferID);
}

void BasicQuad::render() {
    update();
    int current;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current); // This is just to make sure we put things back to the way they were beforehand

    glBindVertexArray(vertexArrayID);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.matrix);
    glBindTexture(GL_TEXTURE_2D, texture.texID);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(current);
}

Vector anGL::BasicQuad::getDims() {
    return Vector(width, height, 0) * mScale;
}