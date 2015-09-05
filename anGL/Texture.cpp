#include "Texture.h"
#include <stdio.h>
#include <gl\glew.h>
#include <assert.h>

using namespace anGL;

#pragma pack(1)
//! Represents info about the bmp file itself
struct BitmapFileInfo { 				//Bitmap File Header
    int8_t type[2];			//this is the BM info;
    uint32_t size;		//file size;
    int16_t empty1;		//reserved space;
    int16_t empty2;		//reserved space;
    uint32_t bitoffset;		//4 bytes to tell us where the data is
};
#pragma pack()

#pragma pack(1)
//! Represents the info header stored inside the bmp that describes the image
struct BitmapInfoHeader {//Bitmap Info Header
    uint32_t headersize;	//size of this data in the file 40 bytes
    uint32_t width, height;	//self explainitory;
    uint32_t planes;		//this is pointless and has to always be set to 1;
    uint32_t bitcount;		//24 = 24 bit, 8 = 8bit, etc, this is the colour bit
    uint32_t comp;		//compression type; 0 = rgb, 1 = RLE8, 2 RLE4, 3 = BITFIELDS
    uint32_t imasize; 		//size of image
    uint32_t ppmX, ppmY; 	//Pixels Per Meter in the x & y planes;
    uint32_t coluse, colimport; 	//# of Colours used, & # of important colours
};
#pragma pack()


Texture::Texture(string location) {
    glGenTextures(1, &texID);
    load(location);
}

Texture::Texture() {
    glGenTextures(1, &texID);
    loaded = false;
}

Texture::~Texture() {
    glDeleteTextures(1, &texID);
}


bool Texture::load(string location) {
    bool result = false;
    if(image.loadBMP24(location)) {
        updateTexture();
        setFilter(GL_NEAREST, GL_NEAREST);
        setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
        //glGenerateMipmap(GL_TEXTURE_2D);
        result = true;
    }
    loaded = result;
    return result;
}

void Texture::setImage(Image& img) {
    assert(img.loaded);
    if(img.loaded) {
        image = img;
        updateTexture();
        setFilter(GL_NEAREST, GL_NEAREST);
        setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
        loaded = true;
    }
}

void Texture::updateTexture(){
    if(image.loaded) {
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.image);
    }
}

void Texture::setFilter(GLenum min, GLenum mag) {
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
}

void Texture::setWrap(GLenum wrap_S, GLenum wrap_T) {
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_T);
}

/*!
    \param tileSize the tile of the tile in both width and height
    \param tiles the array of tile indexes
    \param width how many tiles there are in the x direction
    \param height same as width but in the y direction
    \param source an Image to pull tiles out of or image if source is set to NULL
    \warning width and height are both for how many tiles there are in each direction, not the indended size of the resulted
    image which is calucalated by (width * tileSize) * (height * tileSize)
*/
void Texture::tile(uint8_t tileSize, uint16_t * tiles, uint16_t width, uint16_t height, Image * source) {
    if(source == NULL) {
        assert(loaded);
        source = &image;
    }
    Image result;
    result.height = height * tileSize;
    result.width = width * tileSize;
    result.size = result.width * result.height;
    result.image = new uint32_t[result.size];
    uint32_t * tile = new uint32_t[tileSize * tileSize];
    uint32_t current, xPlace, yPlace, tileX, tileY, tileNo = 0, numTiles = source->size / (tileSize*tileSize);
    for(uint16_t currentTile = 0; currentTile < height * width; currentTile++) {
        assert(tiles[currentTile] < numTiles);
        current = 0;
        xPlace = tileSize * (currentTile % width);
        yPlace = currentTile / width*tileSize;
        tileX = tileSize * (tiles[currentTile] % (source->width / tileSize));
        tileY = (tiles[currentTile] * tileSize / source->height) * tileSize;
        source->subImage(tile, tileX, tileY, tileSize, tileSize);
        uint32_t stride = tileSize*width;
        for(uint32_t yStride = yPlace; yStride < yPlace + tileSize; yStride++) {
            for(uint32_t xStride = xPlace; xStride < xPlace + tileSize; xStride++) {
                result.image[xStride + (yStride*stride)] = tile[current++];
            }
        }
    }
    delete[] tile;
    result.loaded = true;
    setImage(result);
}

void Texture::subTile(uint8_t tileSize, uint16_t * tiles, uint16_t xOffset, uint16_t yOffset, uint16_t width, uint16_t height, Image * source){
    if(loaded) {
        if(source == NULL) {
            source = &image;
        }
        uint32_t * tile = new uint32_t[tileSize * tileSize];
        uint32_t current, xPlace, yPlace, tileX, tileY, tileNo = 0, numTiles = source->size / (tileSize*tileSize);
        for(uint16_t currentTile = 0; currentTile < height * width; currentTile++) {
            assert(tiles[currentTile] < numTiles);
            current = 0;
            xPlace = tileSize * (currentTile % width);
            yPlace = currentTile / width*tileSize;
            tileX = tileSize * (tiles[currentTile] % (source->width / tileSize));
            tileY = (tiles[currentTile] * tileSize / source->height) * tileSize;
            source->subImage(tile, tileX, tileY, tileSize, tileSize);
            uint32_t stride = tileSize*width;
            for(uint32_t yStride = yPlace; yStride < yPlace + tileSize; yStride++) {
                for(uint32_t xStride = xPlace; xStride < xPlace + tileSize; xStride++) {
                    image.image[xStride + (yStride*stride)] = tile[current++];
                }
            }
        }
        delete[] tile;
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, width*tileSize, height*tileSize, GL_RGBA, GL_UNSIGNED_BYTE, image.image);
        setFilter(GL_NEAREST, GL_NEAREST);
        setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
    }
}

Image::Image() {
    loaded = false;
    image = NULL;
    width = height = size = 0;
    alphaMask = 0xFF00FF;
}

Image::Image(Image & other) {
    if(other.loaded) {
        width = other.width;
        height = other.height;
        size = width * height;
        alphaMask = other.alphaMask;
        image = new uint32_t[size];
        for(uint32_t x = 0; x < height; x++) {
            for(uint32_t y = 0; y < width; y++) {
                image[y + (x*width)] = other.image[y + (x*width)];
            }
        }
        loaded = true;
    }
    else {
        image = NULL;
        width = height = size = 0;
    }
}

Image::Image(string location) {
    alphaMask = 0xFF00FF;
    if(!loadBMP24(location)) { //error opening image, just create an empty 2 by 2 image
        image = NULL;
        width = height = size = 0;
        loaded = false;
    }
}

bool Image::loadBMP24(string location) {
    bool result = false;
    BitmapFileInfo fileHeader;
    BitmapInfoHeader infoHeader;
    FILE * fp = fopen(location.c_str(), "rb");
    if(fp) {
        fread(&fileHeader, sizeof(BitmapFileInfo), 1, fp);
        if(!strncmp((char*)fileHeader.type, "BM", 2)) {
            fread(&infoHeader, sizeof(BitmapInfoHeader), 1, fp);
            assert(!(infoHeader.bitcount == 24));
            fseek(fp, fileHeader.bitoffset, SEEK_SET);
            width = infoHeader.width;
            height = infoHeader.height;
            size = width * height;
            this->image = new uint32_t[size];
            uint8_t r, g, b, A = 0xFF;
            int invert = 0;
            for(uint32_t i = 0; i < height; i++) {
                for(uint32_t z = 0; z < width; z++) {
                    fread(&b, 1, 1, fp);
                    fread(&g, 1, 1, fp);
                    fread(&r, 1, 1, fp);
                    if((r << 16 | g << 8 | b) == alphaMask) {
                        A = 0;
                    }
                    else {
                        A = 0xFF;
                    }
                    invert = (height - 1) - i;
                    image[z + (invert*width)] = (A << 24 | b << 16 | g << 8 | r);
                }
            }
            fclose(fp);
            loaded = true;
            result = true;
        }
    }
    return result;
}

/*!
    \param startX starting point in the X direction of this image
    \param startY starting point in the Y direction of this image
    \param subWidth the width of the new image
    \param subHeight the height of the new image

    returns an empty image if startX + subWidth is larger than this instance's width,
    same thing for the height or if subWidth * subHeight is larger than the image's size
*/
Image Image::subImage(uint32_t startX, uint32_t startY, uint32_t subWidth, uint32_t subHeight) {
    Image result;
    assert(loaded);
    assert((subWidth * subHeight <= size));
    assert(startX + subWidth <= width);
    assert(startY + subHeight <= height);
    if(loaded && (subWidth * subHeight <= size)) {
        result.width = subWidth;
        result.height = subHeight;
        result.size = subWidth * subHeight;
        result.image = new uint32_t[result.size];
        uint32_t * start = &image[startX + (startY*width)];
        uint32_t stride = width - subWidth;
        for(uint32_t yStride = 0; yStride < subHeight; yStride++) {
            for(uint32_t xStride = 0; xStride < subWidth; xStride++) {
                result.image[xStride + (yStride*subWidth)] = start[xStride + (yStride*stride) + (yStride*subWidth)];
            }
        }
        result.loaded = true;
    }
    return result;
}

/*!
    \param destination an array of uint32_t's that will be filled with the image data
    works the same as the other overload but instead of returning a new BMP containing the subImage it puts
    it all into destination. Usefull (and is used) for pulling out a tile.
*/
bool Image::subImage(uint32_t * destination, uint32_t startX, uint32_t startY, uint32_t subWidth, uint32_t subHeight) {
    bool result = false;
    assert(loaded);
    assert((subWidth * subHeight <= size));
    assert(startX + subWidth <= width);
    assert(startY + subHeight <= height);
    if(loaded && (subWidth * subHeight <= size)) {
        uint32_t size = subWidth * subHeight;
        uint32_t * start = &image[startX + (startY*width)];
        uint32_t stride = width - subWidth;
        for(uint32_t yStride = 0; yStride < subHeight; yStride++) {
            for(uint32_t xStride = 0; xStride < subWidth; xStride++) {
                destination[xStride + (yStride*subWidth)] = start[xStride + (yStride*stride) + (yStride*subWidth)];
            }
        }
        result = true;
    }
    return result;
}

/*!
    if other.loaded is true does a full copy, otherwise frees image and sets everything to 0
*/
Image & Image::operator=(Image& other) {
    if(other.loaded) {
        width = other.width;
        height = other.height;
        size = width * height;
        delete[] image;
        image = new uint32_t[size];
        loaded = true;
        for(uint32_t x = 0; x < height; x++) {
            for(uint32_t y = 0; y < width; y++) {
                image[y + (x*width)] = other.image[y + (x*width)];
            }
        }
    } else {
        delete[] image;
        image = NULL;
        width = height = size = 0;
        loaded = false;
    }
    return *this;
}

Image::~Image() {
    delete[] image;
}
