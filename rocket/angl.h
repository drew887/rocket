#pragma once
#ifndef ANGL_H
#define ANGL_H

#include <Windows.h>
#include <gl\gl.h>

namespace anGL {

    int createOpenGLWin(HINSTANCE hInstance, const wchar_t * windowName, int width, int height, LRESULT(CALLBACK *windowCallback)(HWND, UINT, WPARAM, LPARAM));
}

#endif