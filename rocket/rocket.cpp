#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl\glew.h>

#include "angl.h"
#include "Program.h"
#include "Matrix.h"
#include "BasicQuad.h"

#include <time.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void render();

using namespace anGL;

HDC device;

int uniformWorld;

BasicQuad * quad, *du;
Matrix * perMod = NULL;
bool keys[256] = { 0 };

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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Matrix world;
    //world.perspective(90, 1, 0.2f, 10);
#define squareS 3.f
    world.orthographic(squareS, -squareS, -squareS, squareS, 0.2f, 10);
    perMod = &world;
    uniformWorld = glGetUniformLocation(prog.programID, "world");
    glUniformMatrix4fv(uniformWorld, 1, GL_FALSE, world.matrix);

    BasicQuad one(1, 1);
    quad = &one;
    one.Translate(0, 0, -3);
    one.texture.image.alphaMask = 0xFFFFFF;
    one.texture.load("vtr.bmp");
    one.setLocs(prog.programID);

    BasicQuad two(4, 4);
    du = &two;
    two.Translate(0, 0, -3.001f);
    two.setLocs(prog.programID);

    srand((int)time(NULL));
    unsigned short mapw = 4;
    uint16_t map[16] = { 
        0, 1, 1, 2,
        3, 4, 4, 5,
        3, 4, 4, 5,
        6, 7, 7, 8 
    };
    BMP tileset("ship.bmp");
    two.texture.tile(16, map, mapw, mapw, &tileset);
    
    MSG msg = { 0 };

    glClearColor(0.0f, 0.8f, 0.8f, 1.0f);
    bool loop = true;

    while(loop) {
        render();
        if(keys['W'] && one.position.y < 1.5f) {
            one.Translate(0, 0.1f, 0.f);
        }
        else if(keys['S'] && one.position.y > -1.5f) {
            one.Translate(0, -0.1f, 0.f);
        }
        if(keys['A'] && one.position.x > -1.5f) {
            one.Translate(-0.1f, 0, 0.f);
        }
        if(keys['D'] && one.position.x < 1.5f) {
            one.Translate(0.1f, 0, 0.f);
        }
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
        break;
    }
    case WM_SIZE:
        glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
        if(perMod) {
            perMod->perspective(90, LOWORD(lParam) / ((float)HIWORD(lParam)), 0.2f, 10);
        }
        break;
    case WM_KEYDOWN:
        keys[wParam] = true;
        break;
    case WM_KEYUP:
        keys[wParam] = false;
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
