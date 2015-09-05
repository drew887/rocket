#pragma once
#ifndef ANGL_TEXTURE_H
#define ANGL_TEXTURE_H
#include <string>
#include <stdint.h>
#include <gl\glew.h>

using std::string;
namespace anGL {
    //! Represents abstract 32bit RGBA data in 2 dimensions
    class Image {
    public:
        Image(string location);
        Image();
        Image(Image& other);
        bool loadBMP24(string location); //! Reads in image data from a 24bit BMP and turns it into 32bit RGBA data
        Image subImage(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height); //! Returns an Image that contains the data stored between width and height within this Image
        bool subImage(uint32_t * destination, uint32_t startX, uint32_t startY, uint32_t width, uint32_t height); //! Functions as above but dumps the data into destination, note destination must be pre-allocated
        Image& operator=(Image& other);

        uint32_t width, height, size, alphaMask;
        uint32_t * image;
        bool loaded;
        ~Image();
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
        void setImage(Image& img);
		//! Set the min and mag filters for the openGL texture
        void setFilter(GLenum min, GLenum mag);
        //! Sets the wrap functions in the S and T directions for the texture
        void setWrap(GLenum wrap_S, GLenum wrap_T);
        //! Used to create a tiled texture reading from source or if source is null from image
        void tile(uint8_t tileSize, uint16_t * tiles, uint16_t width, uint16_t height, Image * source = NULL);
        //! Updates a subsection of the texture, or the entire texture if the dimensions match the current Image
        void subTile(uint8_t tileSize, uint16_t * tiles, uint16_t xOffset, uint16_t yOffset, uint16_t width, uint16_t height, Image * source);
        void updateTexture(); //! Recreates the texture with the data inside image.
        
        bool loaded;
        Image image; //! The actual image data
        unsigned int texID;
    };
}
#endif
