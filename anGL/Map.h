/*----------------------------------------------*\
|                                                |
|                      Map.h                     |
| Just a small class to handle batch rendering of|
| BasicPrimitives "on top" of a background, aka  |
| after the background. It doesn't force them to |
| be on top, its up to their Z coordinates if    |
| Depth testing has been turned on, other wise   |
| they will be on top of the background.         |
\*----------------------------------------------*/
#pragma once
#ifndef ANGL_MAP_H
#define ANGL_MAP_H

#include "BasicQuad.h"
#include "Texture.h"
#include <vector>

namespace anGL {
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
        int modelLocation;
    };

    class TiledMap : public BasicMap {
    public:
        TiledMap(float width, float height, Image & tileSet);
        virtual ~TiledMap();
        void tile(uint8_t tileSize, uint16_t width, uint16_t height, uint16_t * tileArray);
    protected:
        std::vector<uint16_t> tiles;
        uint8_t tileSize;
        Image tileSet;
    };
}
#endif