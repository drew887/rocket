#pragma once
#ifndef ANGL_TEXTURE_H
#define ANGL_TEXTURE_H
#include <string>
#include <stdint.h>

using std::string;

class Texture{

public:
    Texture(string location);
    Texture();
    bool load(string location);
    ~Texture();
    unsigned int texID, samplerID;
};


class BMP {
public:
    BMP(string location);
    BMP();
    bool load(string location);
    uint32_t width, height;
    uint32_t * image;
    ~BMP();
};



#endif