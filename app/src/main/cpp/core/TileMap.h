//
// Created by bradley on 6/23/23.
//

#ifndef RENDERERD_DREAM_TILEMAP_H
#define RENDERERD_DREAM_TILEMAP_H

#include "Entity.h"

namespace gdg{
class TileMap:public gdg::Entity{
public:
    TileMap();
    void generateTileMap(entitySpecs2d* specs, int tileMapCount);
    void swapTileMaps2d(int direction);
    void scrollTileMap(float deltaX, float deltaY);
    void drawTileMap();
    void drawMatTileMap();
    void loadMapDrawIndices(float* inIndices, size_t size);
    void loadAnimationMap(float* inAnimMap, size_t mapSize);
    ~TileMap();

protected:

private:

    };
}

#endif //RENDERERD_DREAM_TILEMAP_H


