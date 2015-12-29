/*-------------------------------------------------*\
|                                                   |
|                     angl.h                        |
| anGL is basically just a helper library, it tries |
| to interfere as little as possible while still    |
| giving you come classes such as sprites and maps  |
| if you want those kinds of things.                |
|                                                   |
| It can be used for as little as opening an openGL |
| window, or as far as some light 2d spite and map  |
| handling like the demo included in the repo shows |
|                                                   |
| At this time there aren't classes for handling 3D |
| models but the idea is definitely on the table.   |
\*-------------------------------------------------*/

#pragma once
#ifndef ANGL_H
#define ANGL_H


#include <vector>
#include <ctype.h>
#include <GL/glew.h>

namespace anGL {
#ifdef _WIN32
#include <Windows.h>
    HWND createOpenGLWin(HINSTANCE hInstance, const wchar_t * windowName, int width, int height, const int * attribs,LRESULT(CALLBACK *windowCallback)(HWND, UINT, WPARAM, LPARAM));
#endif
    std::vector<uint16_t> readCSV(const char * loc); ///Reads in a csv of uint16_ts and returns a vector of the values, useful for tile maps
}

#endif
