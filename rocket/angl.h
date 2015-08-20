#pragma once
#ifndef ANGL_H
#define ANGL_H

#include <Windows.h>
#include <gl\glew.h>
#include <gl\wglew.h>

//! main namespace for Rocket
namespace anGL {

    //! used to create an openGL 3.3 window
    HWND createOpenGLWin(HINSTANCE hInstance, const wchar_t * windowName, int width, int height, const int * attribs,LRESULT(CALLBACK *windowCallback)(HWND, UINT, WPARAM, LPARAM));

}

#endif