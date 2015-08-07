#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/GL.h>

#include "angl.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void render();

HGLRC openGLContext;

using namespace anGL;

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    MSG msg = { 0 };
    if(createOpenGLWin(hInstance, L"WindowTest", 640, 480, WndProc)) { //returns 0 upon success
        return 1;
    }
    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        render();
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_CREATE: {
        HDC windowDC = GetDC(hWnd);
        openGLContext = wglCreateContext(windowDC);
        wglMakeCurrent(windowDC, openGLContext);
        break;
    }
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_DESTROY:
        wglDeleteContext(openGLContext);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;

}

void render() {
    
}
