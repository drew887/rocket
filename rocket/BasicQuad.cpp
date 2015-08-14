#include "BasicQuad.h"
#include <gl\glew.h>
using namespace anGL;

BasicQuad::BasicQuad(float width, float height, int programID) {
    verticies = new float[8]{
        0, 0,
        width, 0,
        0, height,
        width, height
    };
    float texts[] = {
        0, 0,
        1, 0,
        0, 1,
        1, 1
    };

    int current = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current);
    glBindVertexArray(0);
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    bool loaded = texture.load("type.bmp");
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, verticies, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &texCoordBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, texts, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    if(programID >= 0) {
        modelLoc = glGetUniformLocation(programID, "model");
        sampleLoc = glGetUniformLocation(programID, "sample");
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.matrix);
    }
    
    
    glBindVertexArray(current);
}

BasicQuad::~BasicQuad() {
    delete[] verticies;
    //int current;
    //glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current);
    //glBindVertexArray(0);
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteBuffers(1, &texCoordBufferID);
    glDeleteVertexArrays(1, &vertexArrayID);
    //glBindVertexArray(current);
}

void BasicQuad::Render() {
    int current;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current);

    glBindVertexArray(vertexArrayID);
    //model = trans *  rot * scale;
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.matrix);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.texID);
    glUniform1i(sampleLoc, 0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(current);
}