#include "BasicPrimitive.h"
#include <gl\glew.h>

using namespace anGL;
/*!
    Initializes verticies to 0 (aka NULL) as verticies will be allocated by the child class' constructor.
    Also generates the VAO and VBO for the Primitive but doesn't fill them with anything, deletion of these objects are
    handled by the BasicPrimitive destructor.
*/
BasicPrimitive::BasicPrimitive(){
    glGenVertexArrays(1, &vertexArrayID);
    glGenBuffers(1, &vertexBufferID);
    modelLoc = 0;
    verticies = 0;
}
/*!
    deletes the array of verticies and the VAO and VBO objects.
*/
BasicPrimitive::~BasicPrimitive(){
    delete[] verticies;
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteVertexArrays(1, &vertexArrayID);
}

void anGL::BasicPrimitive::update(){
    model = (mTranslation * mScale * mRotation);
}

void BasicPrimitive::translate(Vector npos){
    mTranslation.translate(npos.x, npos.y, npos.z);
    position.x = mTranslation.matrix[12];
    position.y = mTranslation.matrix[13];
    position.z = mTranslation.matrix[14];
}

void BasicPrimitive::translate(float amountX, float amountY, float amountZ){
    translate(Vector(amountX, amountY, amountZ));
}

void BasicPrimitive::setTranslate(Vector npos){
    mTranslation.setTranslation(npos.x, npos.y, npos.z);
    position.x = mTranslation.matrix[12];
    position.y = mTranslation.matrix[13];
    position.z = mTranslation.matrix[14];
}

void BasicPrimitive::setTranslate(float amountX, float amountY, float amountZ){
    setTranslate(Vector(amountX, amountY, amountZ));
}

void BasicPrimitive::rotate(float deg, float amountX, float amountY, float amountZ){
    mRotation.rotate(deg, amountX, amountY, amountZ);
}

void anGL::BasicPrimitive::setRotate(float deg, float amountX, float amountY, float amountZ){
    mRotation.setRotation(deg, amountX, amountY, amountZ);
}

void BasicPrimitive::scale(float amountX, float amountY, float amountZ){
    mScale.scale(amountX, amountY, amountZ);
}

void anGL::BasicPrimitive::setScale(float amountX, float amountY, float amountZ){
    mScale.setScale(amountX, amountY, amountZ);
}
