#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl\glew.h>

#include "angl.h"
#include "Program.h"

#include <stdio.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void render();

using namespace anGL;

HDC device;

unsigned int vao, vbo;

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    MSG msg = { 0 };

    HWND windowHandle = createOpenGLWin(hInstance, L"WindowTest", 640, 480, WndProc);
    if(windowHandle == 0) { 
        return 1;
    }
    device = GetDC(windowHandle);
    Program prog;
    Shader vert, frag;
    vert.load("vertex.glsl", GL_VERTEX_SHADER);
    frag.load("fragment.glsl", GL_FRAGMENT_SHADER);
    prog.attachShader(&vert);
    prog.attachShader(&frag);
    prog.linkProgram();
    glUseProgram(prog.programID);

    float verts[] = {
        -0.5, -0.5,
        0.0, 0.5,
        0.5, -0.5
    };
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glClearColor(0.0, 1.0, 1.0, 1.0);
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
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_DESTROY: {
        HGLRC context = wglGetCurrentContext();
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(context);
    }
        break;
    case WM_SIZE:
        glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;

}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    SwapBuffers(device);
}
