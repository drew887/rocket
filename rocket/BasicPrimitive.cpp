#include "BasicPrimitive.h"
#include <gl\glew.h>

using namespace anGL;

BasicPrimitive::BasicPrimitive(){
    glGenVertexArrays(1, &vertexArrayID);
    glGenBuffers(1, &vertexBufferID);
}


BasicPrimitive::~BasicPrimitive(){
    delete[] verticies;
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteVertexArrays(1, &vertexArrayID);
}

void anGL::BasicPrimitive::Translate(Vector npos){
    model.translate(npos.x, npos.y, npos.z);
    position.x = model.matrix[12];
    position.y = model.matrix[13];
    position.z = model.matrix[14];
}

void anGL::BasicPrimitive::Translate(float amountX, float amountY, float amountZ){
    Translate(Vector(amountX, amountY, amountZ));
}

void anGL::BasicPrimitive::Rotate(float deg, float amountX, float amountY, float amountZ){
    model.rotate(deg, amountX, amountY, amountZ);
}

void anGL::BasicPrimitive::Scale(float amountX, float amountY, float amountZ){
    model.scale(amountX, amountY, amountZ);
}
