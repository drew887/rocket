#include "Shader.h"
#include <gl\glew.h>
#include <gl\wglew.h>

using namespace anGL;

anGL::Shader::Shader() {
    shaderID = shaderType = 0;
}

anGL::Shader::~Shader() {
    glDeleteShader(shaderID);
}

#include <fstream>
using namespace std;
bool anGL::Shader::load(string path, int type) {
    bool result = true;
    fstream fin;
    string shader;
    fin.open(path, fstream::in);
    if(fin.is_open()) {
        while(!fin.eof()) {
            string line;
            getline(fin, line);
            shader += (line + '\n');
        }
        shaderID = glCreateShader(type);
        const char * source = shader.c_str();
        glShaderSource(shaderID, 1, &source, NULL);
        glCompileShader(shaderID);
        int compileStatus;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
        if(compileStatus == GL_FALSE) {
            result = false;
        }
        shaderType = type;
    }
    return result;
}