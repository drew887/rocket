#include "Shader.h"
#include <gl\glew.h>
#include <gl\wglew.h>

using namespace anGL;

Shader::Shader() {
    shaderID = shaderType = 0;
}

Shader::~Shader() {
    glDeleteShader(shaderID);
}

#include <vector>
#include <fstream>

using namespace std;
/*!
    \param type either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
    Reads in a file at path, creates an openGL shader object, and then compiles it
*/
bool Shader::load(string path, int type) {
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
            GLint maxLength = 0;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);
            FILE * pp = fopen("Shaderlog.txt", "w");
            for(auto i : infoLog) {
                fprintf(pp, "%c", i);
            }
            fclose(pp);
            result = false;
        }
        shaderType = type;
    }
    return result;
}