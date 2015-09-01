#pragma once
#ifndef ANGL_H
#define ANGL_H

#include <Windows.h>
#include <vector>
#include <gl\glew.h>
#include <gl\wglew.h>
#include <ctype.h>

namespace anGL {
    HWND createOpenGLWin(HINSTANCE hInstance, const wchar_t * windowName, int width, int height, const int * attribs,LRESULT(CALLBACK *windowCallback)(HWND, UINT, WPARAM, LPARAM));
    std::vector<uint16_t> readCSV(const char * loc);
}

#endif