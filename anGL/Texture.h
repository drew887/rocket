#pragma once
#ifndef ANGL_TEXTURE_H
#define ANGL_TEXTURE_H
#include <string>
#include <stdint.h>
#include <gl\glew.h>

using std::string;
namespace anGL {
    class Image {
    public:
        Image(string location);
        Image();
        Image(Image& other);
        bool loadBMP24(string location);
        Image subImage(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height);
        bool subImage(uint32_t * destination, uint32_t startX, uint32_t startY, uint32_t width, uint32_t height);
        Image& operator=(Image& other);

        uint32_t width, height, size, alphaMask;
        uint32_t * image;
        bool loaded;
        ~Image();
    };

    class Texture {
    public:
        Texture(string location);
        Texture();
        ~Texture();
        bool load(string location);
        void setImage(Image& img);
        void setFilter(GLenum min, GLenum mag);
        void setWrap(GLenum wrap_S, GLenum wrap_T);
        void tile(uint8_t tileSize, uint16_t * tiles, uint16_t width, uint16_t height, Image * source = NULL);
        void subTile(uint8_t tileSize, uint16_t * tiles, uint16_t xOffset, uint16_t yOffset, uint16_t width, uint16_t height, Image * source);
        void updateTexture();

        bool loaded;
        Image image;
        unsigned int texID;
    };
}
#endif