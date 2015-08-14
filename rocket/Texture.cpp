#include "Texture.h"
#include <stdio.h>
#include <gl\glew.h>


#pragma pack(1)

struct BitmapFileInfo { 				//Bitmap File Header
    int8_t type[2];			//this is the BM info;
    uint32_t size;		//file size;
    int16_t empty1;		//reserved space;
    int16_t empty2;		//reserved space;
    uint32_t bitoffset;		//4 bytes to tell us where the data is
};

#pragma pack()

#pragma pack(1)

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
    //glGenTextures(1, &texID);
    load(location);
}

Texture::Texture(){
    //glGenTextures(1, &texID);
}

Texture::~Texture() {
    glDeleteTextures(1, &texID);
}


bool Texture::load(string location){
    bool loaded = false;
    BMP image;
    if(image.load(location)) {
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.image);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glGenerateMipmap(GL_TEXTURE_2D);



        //glGenSamplers(1, &samplerID);
        loaded = true;
    }
    else {
        exit(-1);
    }
    return loaded;
}

BMP::BMP() {
}

BMP::BMP(string location) {
    if(!load(location)) { //error opening image, just create an empty 2 by 2 image
        image = NULL;
        width = height = 0;
    }
}

bool BMP::load(string location) {
    bool result = false;
    BitmapFileInfo fileHeader;
    BitmapInfoHeader infoHeader;
    FILE * fp = fopen(location.c_str(), "rb");
    if(fp) {
        fread(&fileHeader, sizeof(BitmapFileInfo), 1, fp);
        fread(&infoHeader, sizeof(BitmapInfoHeader), 1, fp);
        fseek(fp, fileHeader.bitoffset, SEEK_SET);
        width = infoHeader.width;
        height = infoHeader.height;
        this->image = new uint32_t[width * height];
        uint8_t r, g, b, A = 0;
        int invert = 0;
        for(uint32_t i = 0; i < height; i++) {
            for(uint32_t z = 0; z < width; z++) {
                r, g, b, A = 0;
                fread(&r, 1, 1, fp);
                fread(&g, 1, 1, fp);
                fread(&b, 1, 1, fp);
                invert = (height - 1) - i;
                image[z + (i*width)] = (A << 24 | r << 16 | g << 8 | b);
            }
        }
        fclose(fp);
        result = true;
    }

    return result;
}

BMP::~BMP() {
    delete[] image;
}