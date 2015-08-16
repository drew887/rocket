#pragma once
#ifndef ANGL_TEXTURE_H
#define ANGL_TEXTURE_H
#include <string>
#include <stdint.h>
#include <gl\glew.h>

using std::string;

class BMP {
public:
    BMP(string location);
    BMP();
    BMP(BMP& other);
    bool load(string location);
    BMP subImage(uint8_t startX, uint8_t startY, uint8_t width, uint8_t height);
    BMP& operator=(BMP& other);

    uint32_t width, height, size;
    uint32_t * image;
    bool loaded;
    ~BMP();
};

class Texture{
protected:
public:
    Texture(string location);
    Texture();
    ~Texture();
    bool load(string location);
    void setImage(BMP& img);
    void setFilter(GLenum min, GLenum mag);
    void setWrap(GLenum wrap_S, GLenum wrap_T);
    //void tile(uint8_t * tiles, uint32_t width, uint32_t height);
    
    bool loaded;
    BMP image;
    unsigned int texID, samplerID;
};

#endif