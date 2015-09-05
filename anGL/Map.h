#pragma once
#ifndef ANGL_MAP_H
#define ANGL_MAP_H

#include "BasicQuad.h"
#include "Texture.h"
#include <vector>

namespace anGL {
    //! Simple holder of a "background" BasicQuad and a vector of BasicPrimitive pointers that are all rendered upon BasicMap::render.
    class BasicMap {
    public:
        BasicMap(float width, float height);
        virtual ~BasicMap();
        virtual void render();
        virtual void setModelLocation(int programID, const char * uniformName);
        virtual void addPrimitives(unsigned int num, BasicPrimitive * addedPrimitives);
        BasicQuad background;
    protected:
        std::vector<BasicPrimitive*> primitives;
        int modelLocation; //!The uniform location to send the BasicPrimitives model Matrix upon rendering
    };
    //! Simple child class holding a vector of tiles representing the tiled Image on background
    class TiledMap : public BasicMap {
    public:
        TiledMap(float width, float height, Image & tileSet);
        virtual ~TiledMap();
        void tile(uint8_t tileSize, uint16_t width, uint16_t height, uint16_t * tileArray);
    protected:
        std::vector<uint16_t> tiles;
        uint8_t tileSize; //! The size of the tiles in tiles
        Image tileSet; //! The Image to pull tiles from
    };
}
#endif