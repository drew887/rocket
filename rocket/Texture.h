#pragma once
#ifndef ANGL_TEXTURE_H
#define ANGL_TEXTURE_H
#include <string>
#include <stdint.h>
#include <gl\glew.h>

using std::string;
namespace anGL {
    class BMP {
    public:
        BMP(string location);
        BMP();
        BMP(BMP& other);
        BMP(BMP&& other); //move constructor?
        bool load(string location);
        BMP subImage(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height);
        bool subImage(uint32_t * destination, uint32_t startX, uint32_t startY, uint32_t width, uint32_t height);
        BMP& operator=(BMP& other);

        uint32_t width, height, size;
        uint32_t * image;
        bool loaded;
        ~BMP();
    };

    class Texture {
    public:
        Texture(string location);
        Texture();
        ~Texture();
        bool load(string location);
        void setImage(BMP& img);
        void setFilter(GLenum min, GLenum mag);
        void setWrap(GLenum wrap_S, GLenum wrap_T);
        void tile(uint8_t tileSize, uint16_t * tiles, uint16_t width, uint16_t height, BMP * source = NULL);

        bool loaded;
        BMP image;
        unsigned int texID, samplerID;
    };
}
#endif