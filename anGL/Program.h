#pragma once
#ifndef ANGL_PROGRAM_H
#define ANGL_PROGRAM_H
#include "Shader.h"
#include <vector>

using std::vector;

namespace anGL {
    //! A basic representation of an openGL program object
    class Program {
    public:
        Program();
        ~Program();
        void attachShader(Shader * shader);
        bool linkProgram();
        unsigned int programID;
        vector<int> shaders;
    };
}
#endif