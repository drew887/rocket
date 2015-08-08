#include "Program.h"
#include <gl\glew.h>

using namespace anGL;

anGL::Program::Program(){
    programID = glCreateProgram();
}


anGL::Program::~Program(){
    for(unsigned int ctr = 0; ctr < shaders.size(); ctr++) {
        glDetachShader(programID, shaders[ctr]  );
    }
    glDeleteProgram(programID);
}

bool anGL::Program::linkProgram() {
    bool result = true;
    glLinkProgram(programID);
    int linkStatus;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
    if(linkStatus == GL_FALSE) {
        result = false;
    }
    return result;
}

void anGL::Program::attachShader(Shader * shader) {
    glAttachShader(programID, shader->shaderID);
}