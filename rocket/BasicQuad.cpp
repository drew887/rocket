#include "BasicQuad.h"
#include <gl\glew.h>
using namespace anGL;

BasicQuad::BasicQuad(float width, float height) {
    width /= 2;
    height /= 2;
    verticies = new float[8]{
        -width, -height,
        width, -height,
        -width, height,
        width, height
    };
   float texts[] = { //reversed tex coords 
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

    sampleLoc = 0;
    glBindVertexArray(current);
}

BasicQuad::~BasicQuad() {
    glDeleteBuffers(1, &texCoordBufferID);
}

void BasicQuad::Render() {
    int current;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current);

    glBindVertexArray(vertexArrayID);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.matrix);
    
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.texID);
    glUniform1i(sampleLoc, 0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(current);
}

void BasicQuad::setLocs(int programID) {
    modelLoc = glGetUniformLocation(programID, "model");
    sampleLoc = glGetUniformLocation(programID, "sample");
}