#include "Map.h"
#include <GL/glew.h>

using namespace anGL;

BasicMap::BasicMap(float width, float height) :background(width, height) {
    modelLocation = 0;
}


BasicMap::~BasicMap() {
    for(unsigned int ctr = 0; ctr < primitives.size(); ctr++) {
        delete primitives[ctr];
    }
}

void BasicMap::render() {
    background.render();
    for(unsigned int ctr = 0; ctr < primitives.size(); ctr++) {
        primitives[ctr]->render();
    }
}

void BasicMap::setModelLocation(int programID, const char * uniformName) {
    modelLocation = glGetUniformLocation(programID, uniformName);
    background.modelLoc = modelLocation;
    for(unsigned int ctr = 0; ctr < primitives.size(); ctr++) {
        primitives[ctr]->modelLoc = modelLocation;
    }
}

void BasicMap::addPrimitives(unsigned int num, BasicPrimitive * addedPrimitives){
    for(unsigned int ctr = 0; ctr < num; ctr++) {
        addedPrimitives[ctr].modelLoc = modelLocation;
        primitives.push_back(&addedPrimitives[ctr]);
    }
}

TiledMap::TiledMap(float width, float height, Image & _tileSet) : BasicMap(width, height) {
    tileSet = _tileSet;
}

TiledMap::~TiledMap() {

}

void TiledMap::tile(uint8_t _tileSize, uint16_t width, uint16_t height, uint16_t * tileArray) {
    tiles = std::vector<uint16_t>(tileArray, tileArray + width*height);
    tileSize = _tileSize;
    background.texture.tile(tileSize, tiles.data(), width, height, &tileSet);
}


