#include "Program.h"
#include <GL/glew.h>

using namespace anGL;

Program::Program(){
    programID = glCreateProgram();
}


Program::~Program(){
    for(unsigned int ctr = 0; ctr < shaders.size(); ctr++) {
        glDetachShader(programID, shaders[ctr]  );
    }
    glDeleteProgram(programID);
}

bool Program::linkProgram() {
    bool result = true;
    glLinkProgram(programID);
    int linkStatus;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
    if(linkStatus == GL_FALSE) {
        result = false;
    }
    return result;
}

void Program::attachShader(Shader * shader) {
    glAttachShader(programID, shader->shaderID);
}