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

int uniformWorld;

BasicQuad * quad, *du;
Matrix * perMod = NULL;

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
#define winh 600
#define winw 600

    int attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, 0,
        0
    };

    HWND windowHandle = createOpenGLWin(hInstance, L"WindowTest", winw, winh, attribs, WndProc);
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
    glEnable(GL_CULL_FACE);

    Matrix world;
    world.perspective(90, 1, 0.2f, 10);
    //world.orthographic(4, -4, -4, 4, 0.2, 10);
    perMod = &world;
    uniformWorld = glGetUniformLocation(prog.programID, "world");
    glUniformMatrix4fv(uniformWorld, 1, GL_FALSE, world.matrix);

    BasicQuad one(2, 2, prog.programID);
    quad = &one;
    one.model.translate(0, 0, -5);

    BasicQuad two(2, 2, prog.programID);
    du = &two;
    two.texture.load("col.bmp");
    two.model.translate(0, 0, -1);

    uint16_t map[16] = { 0};
    for(char i = 0; i < 16; i++) {
        map[i] = i;
    }
    unsigned short mapw = 4;
    two.texture.tile(4, map, mapw, mapw);

    MSG msg = { 0 };

    glClearColor(0.0f, 0.8f, 0.8f, 1.0f);
    bool loop = true;
    Vector oneMove(0, 0, 0.1f);
    while(loop) {
        render();
        if(one.position.z >= -1.5f) {
            oneMove.z = -0.1f;
        }
        else if(one.position.z <= -6.f) {
            oneMove.z = 0.1f;
        }
        one.Translate(oneMove);

        Sleep(16);
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if(msg.message == WM_QUIT) {
                loop = false;
            }
            DispatchMessage(&msg);
        }
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message) {
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
