#pragma once
#ifndef ANGL_TEXTURE_H
#define ANGL_TEXTURE_H
#include <string>
#include <stdint.h>
#include <gl\glew.h>

using std::string;
namespace anGL {

    //! Represents a 24bit BMP file and handles its loading, currently doesn't handle the other forms of BMP
    class BMP {
    public:
        BMP();
        BMP(string location);
        BMP(BMP& other);
        BMP(BMP&& other);
        //!Loads a bmp at location into image
        bool load(string location);
        //! Returns a new anGL::BMP with a copy of the data between the rectagle defined by startX, startY, width, and height
        BMP subImage(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height);
        //! Dumps the subImage data into destination
        bool subImage(uint32_t * destination, uint32_t startX, uint32_t startY, uint32_t width, uint32_t height);
        BMP& operator=(BMP& other);

        uint32_t width, height, size;
        uint32_t * image;
        bool loaded;
        ~BMP();
    };

    //! Represents an openGL texture and holds an anGL::BMP for image data
    class Texture {
    public:
        Texture(string location);
        Texture();
        ~Texture();
        //! Uses location to load a BMP and then creates an openGL textures pointed to by texID
        bool load(string location);
        //! Copies img and loads it into an openGL texture
        void setImage(BMP& img);
        //! Set the min and mag filters for the openGL texture
        void setFilter(GLenum min, GLenum mag);
        //! Sets the wrap functions in the S and T directions for the texture
        void setWrap(GLenum wrap_S, GLenum wrap_T);
        //! Used to create a tiled texture reading from source or if source is null from image
        void tile(uint8_t tileSize, uint16_t * tiles, uint16_t width, uint16_t height, BMP * source = NULL);

        bool loaded;
        BMP image;
        unsigned int texID, samplerID;
    };
}
#endif