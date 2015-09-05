#pragma once
#ifndef ANGL_SHADER_H
#define ANGL_SHADER_H
#include <string>

using std::string;

namespace anGL {
    //! A small utility class for loading in a glsl shader and compiling it
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