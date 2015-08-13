#include "BasicQuad.h"
#include <gl\glew.h>
using namespace anGL;

BasicQuad::BasicQuad(float width, float height, float startX, float startY, int uniformLoc) {
    verticies = new float[8]{
        startX, startY,
        width, startY,
        startX, height,
        width, height
    };
    int current;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current);
    glBindVertexArray(0);
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8, verticies, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    if(uniformLoc >= 0) {
        modelLoc = glGetUniformLocation(uniformLoc, "model");
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.matrix);
    }
    glEnableVertexAttribArray(0);
    glBindVertexArray(current);
}

BasicQuad::~BasicQuad() {
    delete[] verticies;
    //int current;
    //glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current);
    //glBindVertexArray(0);
    glDeleteBuffers(1, &bufferID);
    glDeleteVertexArrays(1, &vertexArrayID);
    //glBindVertexArray(current);
}

void BasicQuad::Render() {
    glBindVertexArray(vertexArrayID);
    model = trans *  rot * scale;
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.matrix);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}