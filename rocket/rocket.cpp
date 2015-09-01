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

BasicPrimitive * character, *background, *reference;
Matrix * perMod = NULL, *cam;
bool keys[256] = { 0 };
int uniformWorld, uniformCam, FPS = 16;
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
    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    
    Matrix camera;
    cam = &camera;
    uniformCam = glGetUniformLocation(prog.programID, "camera");
    glUniformMatrix4fv(uniformCam, 1, GL_FALSE, camera.matrix);

    Matrix world;
    //world.perspective(90, 1, 0.2f, 50);
#define squareS 3.f
    world.orthographic(squareS, -squareS, -squareS, squareS, 0.2f, 10);
    perMod = &world;
    uniformWorld = glGetUniformLocation(prog.programID, "world");
    glUniformMatrix4fv(uniformWorld, 1, GL_FALSE, world.matrix);

    Sprite one(1, 1);
    character = &one;
    one.translate(0, 0, -3);
    one.texture.image.alphaMask = 0xFFFFFF;
    one.texture.load("vtr.bmp");
    one.modelLoc = glGetUniformLocation(prog.programID, "model");

    BasicQuad two(15, 15);
    background = &two;
    two.translate(0, 0, -3.001f);
    two.setLocs(prog.programID);

    BasicQuad floorr(4, 4);
    reference = &floorr;
    floorr.setLocs(prog.programID);
    floorr.scale(1, 1, 0);
    floorr.rotate(-90, 1, 0, 0);
    floorr.translate(0, -1.5, -3);

    srand((int)time(NULL));
    unsigned short mapw = 4;
    uint16_t map[16] = {
        0, 1, 1, 2,
        3, 4, 4, 5,
        3, 4, 4, 5,
        6, 7, 7, 8
    };
    vector<uint16_t> cmap = readCSV("overworld.csv");
    Image tileset("ship.bmp"), over("overworld.bmp");
    floorr.texture.tile(16, map, mapw, mapw, &tileset);
    two.texture.tile(8, cmap.data(), 30, 30, &over);


    MSG msg = { 0 };

    glClearColor(0.0f, 0.8f, 0.8f, 1.0f);
    bool loop = true;
    clock_t startTime = clock(), curTime, temp = 0;
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
        //floorr.rotate(-1, 1, 0, 0);
        //floorr.rotate(-1, 0, 0, 1);
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
            perMod->perspective(360, LOWORD(lParam) / ((float)HIWORD(lParam)), 0.2f, 50);
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
    glUniformMatrix4fv(uniformCam, 1, GL_FALSE, cam->matrix);
    character->render();
    background->render();
    reference->render();
    SwapBuffers(device);
}
void keyLoop(int deltaTime) {
    Vector upMove;
    float movement = 3 * (float(deltaTime) / CLOCKS_PER_SEC);
    if(keys['W']) {
        upMove.y = movement;
    }
    else if(keys['S']) {
        upMove.y = -movement;
    }
    if(keys['A']) {
        upMove.x = -movement;
    }
    else if(keys['D']) {
        upMove.x = movement;
    }
    if(keys[VK_ESCAPE]) {
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
        FPS = 25;
        keys[VK_F3] = false;
    }
    character->translate(upMove);
    if(character->position.x > 1.5f) {
        character->setTranslate(1.5f, character->position.y, character->position.z);
    }
    else if(character->position.x < -1.5f) {
        character->setTranslate(-1.5f, character->position.y, character->position.z);
    }
    if(character->position.y > 1.5f) {
        character->setTranslate(character->position.x, 1.5f, character->position.z);
    }
    else if(character->position.y < -1.5f) {
        character->setTranslate(character->position.x, -1.5f, character->position.z);
    }
    if(keys[VK_RIGHT]) {
        cam->translate(-0.1f, 0, 0);
    }
    if(keys[VK_LEFT]) {
        cam->translate(0.1f, 0, 0);
    }
    if(keys[VK_DOWN]) {
        cam->translate(0, 0.1f, 0.f);
    }
    if(keys[VK_UP]) {
        cam->translate(0, -0.1f, 0.f);
    }
    if(keys['Q']) {
        cam->translate(0, 0, 0.1f);
    }
    if(keys['E']) {
        cam->translate(0, 0, -0.1f);
    }
}