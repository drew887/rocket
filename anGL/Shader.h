/*-------------------------------------*\
|                                       |
|                Shader.h               |
| Shader is a class to ease the creation|
| and clean up of openGL shader objects |
\*-------------------------------------*/
#pragma once
#ifndef ANGL_SHADER_H
#define ANGL_SHADER_H
#include <string>

using std::string;

namespace anGL {
    class Shader
    {
    public:
        Shader();
        ~Shader();
        bool load(string path, int type);
        unsigned int shaderID;
        int shaderType;
    };
}
#endif