#include "Sprite.h"

using namespace anGL;

Sprite::Sprite(float nWidth, float nHeight):width(nWidth), height(nHeight) {

    verticies = new float[8]{
        0, height,
        0, 0,
        width, height,
        width, 0
    };
    float texts[] = { //reversed tex coords 
        0, 0,
        0, 1,
        1, 0,
        1, 1
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


Sprite::~Sprite(){
    glDeleteBuffers(1, &texCoordBufferID);
}

void anGL::Sprite::Render(){
    int current;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current);

    glBindVertexArray(vertexArrayID);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.matrix);
    glBindTexture(GL_TEXTURE_2D, texture.texID);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(current);
}

Vector anGL::Sprite::getDims() {
    return Vector(width, height, 0);
}
