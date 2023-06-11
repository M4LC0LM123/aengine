#ifndef TILEMAP_H
#define TILEMAP_H
#pragma once
#include "cassert"

struct TileMap
{
    int map[mapRows][mapCols];
    Texture2D texture;
    Vector2 tileScale;
    Vector2 frameScale;
    Color color;
    int x, y = 0;
};

void tileCheck(TileMap* tileMap);
int getTileAt(TileMap* tileMap, int x, int y);

void initMap(std::string mapFile, TileMap* tileMap)
{
    loadArray2D(mapFile, tileMap->map);
    for (tileMap->x = 0; tileMap->x < mapRows; tileMap->x++)
    {
        for (tileMap->y = 0; tileMap->y < mapCols; tileMap->y++)
        {
            tileCheck(tileMap);
        }
    }
}

int getTile(TileMap* tileMap)
{
    return tileMap->map[tileMap->x][tileMap->y];
}

Vector2 getTilePos(TileMap* tileMap, int tileIndex)
{
    for (tileMap->x = 0; tileMap->x < mapRows; tileMap->x++)
    {
        for (tileMap->y = 0; tileMap->y < mapCols; tileMap->y++)
        {
            if (getTileAt(tileMap, tileMap->x, tileMap->y) == tileIndex)
            {
                return (Vector2){tileMap->x * tileMap->tileScale.x, tileMap->y * tileMap->tileScale.y};
            }
        }
    }
    return {0};
}

bool isTile(TileMap* tileMap, int tileIndex)
{
    for (tileMap->x = 0; tileMap->x < mapRows; tileMap->x++)
    {
        for (tileMap->y = 0; tileMap->y < mapCols; tileMap->y++)
        {
            if (getTileAt(tileMap, tileMap->x, tileMap->y) == tileIndex)
            {
                return true;
            }
        }
    }
    return false;
}

int getTileAt(TileMap* tileMap, int x, int y)
{
    return tileMap->map[y][x];
}

void setTile(TileMap* tileMap, int tileIndex)
{
    for (tileMap->x = 0; tileMap->x < mapRows; tileMap->x++)
    {
        for (tileMap->y = 0; tileMap->y < mapCols; tileMap->y++)
        {
            tileMap->map[tileMap->y][tileMap->x] = tileIndex;
        }
    }
}

void setTileAt(TileMap* tileMap, int tileIndex, int x, int y)
{
    if (x >= 0 && x <= mapRows)
    {
        if (y >= 0 && y <= mapCols)
        {
            tileMap->map[y][x] = tileIndex;
        }
    }
}

#endif