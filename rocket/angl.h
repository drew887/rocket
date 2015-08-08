#pragma once
#ifndef ANGL_H
#define ANGL_H

#include <Windows.h>
#include <gl\glew.h>
#include <gl\wglew.h>

namespace anGL {

    HWND createOpenGLWin(HINSTANCE hInstance, const wchar_t * windowName, int width, int height, LRESULT(CALLBACK *windowCallback)(HWND, UINT, WPARAM, LPARAM));
}

#endif