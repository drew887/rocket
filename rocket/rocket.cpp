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

BasicQuad * quad;
Matrix * triMod;

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
        0.0, 0.5*sqrtf(0.5), //an equalateral triangle
        0.5, -0.5
    };
    float colours[] = {
        1., 1., 0,
        0., 1., 1.,
        1., 0., 1.
    };
    Matrix world;
    world.perspective(90, 640 / 480.f, 0.2, 10);
    Matrix model;
    triMod = &model;
    model.translate(-0.2, 0, -1);
    model.rotate(90, 0, 0, 1);
    model.scale(0.5, 0.5, 0);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    uniformWorld = glGetUniformLocation(prog.programID, "world");
    glUniformMatrix4fv(uniformWorld, 1, GL_FALSE, world.matrix);
    uniformWorld = glGetUniformLocation(prog.programID, "model");
    glUniformMatrix4fv(uniformWorld, 1, GL_FALSE, model.matrix);
    glBindVertexArray(0);
    
    BasicQuad one(2, 2, 0.f, 0.f, prog.programID);
    quad = &one;
    //one.model.scale(0, 0.1, 0);
    one.rot.rotate(45, 0, 0, 1);
    one.trans.translate(-1, -1, -1);

    glClearColor(0.0, 0.10, 1.0, 1.0);
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
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
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
    quad->Render();
    glBindVertexArray(vao);
    glUniformMatrix4fv(uniformWorld, 1, GL_FALSE, triMod->matrix);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    SwapBuffers(device);
}
