#include "angl.h"

using namespace anGL;

HWND anGL::createOpenGLWin(HINSTANCE hInstance, const wchar_t * windowName, int width, int height, const int * attribs,LRESULT(CALLBACK *windowCallback)(HWND, UINT, WPARAM, LPARAM)) {
    
    WNDCLASS windowClass = { 0 };
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = windowName;
    windowClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.style = CS_OWNDC;
    windowClass.lpfnWndProc = windowCallback;

    if(!RegisterClass(&windowClass)) {
        MessageBoxA(0, "Couldn't register window class!", "Error", 0);
        return 0;
    }
    HWND windowHandle = CreateWindowW(windowClass.lpszClassName, windowClass.lpszClassName,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0, //x and y
        width, height,
        NULL, NULL, //parent window and menu; we want neither
        hInstance,
        NULL); //lparams

    if(!windowHandle) {
        MessageBoxA(0, "Couldn't create window!", "Error", 0);
        return 0;
    }

    PIXELFORMATDESCRIPTOR pixelDescription = {
        sizeof(PIXELFORMATDESCRIPTOR), //this is here incase of future PIXELFORMATDESCRIPTOR versions, like an EX or something
        1, //this says yes we are using a regular PIXELFORMATDESCRIPTOR
        PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL, //these flags are pretty obvious
        PFD_TYPE_RGBA, //shows that we want RGBA rather than index based colours
        32, //colour depth, 32bit for true colour
        0, 0, 0, 0, 0, 0, //These are specifying the number of bitplanes and shift for our RGB, we want these to be 0 for now
        0, 0, //These are the bitplanes and shift for our alpha buffer, we still want these to be 0 since we will be using openGL's instead
        0, //This is how many bitplanes in our accumulation buffer, we want 0
        0, 0, 0, 0, //These are the bitplanes for the RGBA in out accumulation buffer, 0 because we don't have an accumulation buffer
        24, //This is the depth of our depth buffer (tee-hee) 24 or 16 seem to be the standard
        8, //This is the depth of out stencil buffer 8 seems to be pretty good
        0, //This is the number of auxillary buffers, windows doesn't support auxillary buffers at this time
        PFD_MAIN_PLANE, //This is actually not needed and is ignored by windows now, but we stick it here for backwards compatability
        0, //The number of over and underlay planes the high order bytes for over and low order for underlay, up to 15 in either direction
        0, //The layer mask, this is ignored by windows and was used in older versions of openGL
        0, //Specifies the transparancy colour of the underplanes not used in openGL or RGBA colouring
        0, //The damage mask, used in older openGL implementations but ignored now
    };

    HDC windowDC = GetDC(windowHandle);
    int givenFormat = ChoosePixelFormat(windowDC, &pixelDescription); //This is the descriptor that windows returns based on what we wanted with pixelDescription

    if(!SetPixelFormat(windowDC, givenFormat, &pixelDescription)) {
        MessageBoxA(0, "No Matching PFD found!", "Error", 0);
        return 0;
    }

    HGLRC openGLContext = wglCreateContext(windowDC);
    wglMakeCurrent(windowDC, openGLContext);
    
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        MessageBoxA(0, "Error with glew!", "Error", 0);
        return 0;
    }

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(openGLContext);
    openGLContext = wglCreateContextAttribsARB(windowDC, 0, attribs);
    wglMakeCurrent(windowDC, openGLContext);

    return windowHandle;
}

