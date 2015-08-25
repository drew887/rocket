#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl\glew.h>

#include "angl.h"
#include "Program.h"
#include "Matrix.h"
#include "BasicQuad.h"
#include "Sprite.h"

#include <time.h>

using namespace anGL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void keyLoop(int deltaTime);
void render();

BasicPrimitive * character, *background;
Matrix * perMod = NULL;
bool keys[256] = { 0 };
int uniformWorld, FPS = 16;
HDC device;

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

    Sprite one(1, 1);
    character = &one;
    one.Translate(0, 0, -3);
    one.texture.image.alphaMask = 0xFFFFFF;
    one.texture.load("vtr.bmp");
    one.modelLoc = glGetUniformLocation(prog.programID, "model");

    BasicQuad two(4, 4);
    background = &two;
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
    clock_t startTime = clock(), curTime, temp =0;
    time_t currentTime = time(NULL);
    unsigned int frames = 0;
    int sleepTime = 0;
//----------------->
    while(loop) {
        curTime = clock();
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if(msg.message == WM_QUIT) {
                loop = false;
            }
            DispatchMessage(&msg);
        }
        keyLoop(sleepTime);
        render();
        glFinish();
        frames++;
        temp = clock();
        temp -= curTime;
        sleepTime = FPS - temp;
        if(sleepTime > 0) {
            Sleep(sleepTime);
        }
        if(time(NULL) - currentTime >= 1) {
            frames = 0;
            currentTime = time(NULL);
        }
    }
//----------------->
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
    character->Render();
    background->Render();
    SwapBuffers(device);
}
void keyLoop(int deltaTime) {
    Vector upMove;
    float movement = 3 * (float(deltaTime) / CLOCKS_PER_SEC);
    if(keys['W']) {
        //character->Translate(0, 0.1f, 0.f);
        upMove.y = movement;
    }else if(keys['S']) {
        //character->Translate(0, -0.1f, 0.f);
        upMove.y = -movement;
    }
    if(keys['A']) {
        //character->Translate(-0.1f, 0, 0.f);
        upMove.x = -movement;
    }else if(keys['D']) {
        //character->Translate(0.1f, 0, 0.f);
        upMove.x = movement;
    }
    if(keys[VK_ESCAPE] || keys['Q']) {
        PostQuitMessage(0);
    }
    if(keys[VK_F1]) {
        FPS = 16;
        keys[VK_F1] = false;
    }
    if(keys[VK_F2]) {
        FPS = 33;
        keys[VK_F2] = false;
    }
    if(keys[VK_F3]) {
        FPS = 66;
        keys[VK_F3] = false;
    }
    character->Translate(upMove);
    if(character->position.x > 1.f) {
        character->setTranslate(1.f, character->position.y, character->position.z);
    }
    else if(character->position.x < -2.0f) {
        character->setTranslate(-2.0f, character->position.y, character->position.z);
    }
    if(character->position.y > 1.0f) {
        character->setTranslate(character->position.x, 1.0f, character->position.z);
    }
    else if(character->position.y < -2.0f) {
        character->setTranslate(character->position.x, -2.0f, character->position.z);
    }
}