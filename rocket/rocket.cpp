#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl\glew.h>

#include "angl.h"
#include "Program.h"
#include "Matrix.h"
#include "BasicQuad.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void render();

using namespace anGL;

HDC device;

unsigned int vao, vbo, colorVBO;
int uniformWorld;

BasicQuad * quad, * du;
Matrix * triMod, * perMod = NULL;

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    MSG msg = { 0 };
#define winh 600
#define winw 600
    HWND windowHandle = createOpenGLWin(hInstance, L"WindowTest", winw, winh, WndProc);
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
    glEnable(GL_DEPTH_TEST);

    Matrix world;
    world.perspective(90, 1, 0.2, 10);
    //world.orthographic(10, -10, -10, 10, 0.2f, 10);
    perMod = &world;
    uniformWorld = glGetUniformLocation(prog.programID, "world");
    glUniformMatrix4fv(uniformWorld, 1, GL_FALSE, world.matrix);
    BasicQuad one(2, 2, prog.programID);
    quad = &one;
    one.model.scale(0.1, 0.1, 0);
    //one.rot.rotate(-45, 0, 0, 1);
    one.model.translate(-1, -1, -2);

    BasicQuad two(2, 2, prog.programID);
    du = &two;
    two.model.translate(-1, -3, -2);
    two.model.rotate(90, 0, 0, 1);
    
    glClearColor(0.5, 0.5, 0.5, 1.0);
    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        render();
        GLenum errCode;
        const char *errString;
        if((errCode = glGetError()) != GL_NO_ERROR) {
            string error = "none";
            switch(errCode) {
            case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
            case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
            case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
            case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
            }

            MessageBoxA(0, error.c_str(), "ERR", 0);
        }
        //PostQuitMessage(0);
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
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        HGLRC context = wglGetCurrentContext();
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(context);
    }
        break;
    case WM_SIZE:
        glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
        if(perMod) {
            perMod->perspective(90, LOWORD(lParam) / ((float)HIWORD(lParam)), 0.2f, 10);
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;

}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniformMatrix4fv(uniformWorld, 1, GL_FALSE, perMod->matrix);
    quad->Render();
    du->Render();
    SwapBuffers(device);
}
