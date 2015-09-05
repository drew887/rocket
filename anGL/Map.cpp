#include "Map.h"
#include <gl\glew.h>

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
/*!
    \param programID The ID of the program to search in
    \param uniformName The name of the uniform
    sets modelLocaton to the location of the uniform named uniformName in programID.
    modelLocation is used to set modelLoc of the BasicPrimitives in primitives when they are added to the map so they are all
    rendered correctly.
*/
void BasicMap::setModelLocation(int programID, const char * uniformName) {
    modelLocation = glGetUniformLocation(programID, uniformName);
    background.modelLoc = modelLocation;
    for(unsigned int ctr = 0; ctr < primitives.size(); ctr++) {
        primitives[ctr]->modelLoc = modelLocation;
    }
}
/*!
    \param num The number of primitives stored in addedPrimitives
    \param addedPrimitives The array of BasicPrimitives to add
    Adds a series of BasicPrimitives to primitives and sets their modelLoc 
*/
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


