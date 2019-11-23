#ifndef TILETYPE_H
#define TILETYPE_H

enum class TileType
{
    grass = 0,
    sea = 1,
    sand = 2,
    brick = 3,
    clay = 4,
    lava = 5,
    rock = 6,
};

enum class BuildingType
{
    nothing = 0,
    forest = 1,
    stones1 = 2,
    stones2 = 3,
    stones3 = 4,
};

enum class ItemType
{
    nothing = 0,
    lpot = 1,
};

struct MapTile
{
    TileType tile;
    BuildingType building;
    ItemType item;

    MapTile(TileType tile, BuildingType building, ItemType item) : tile(tile), building(building), item(item) {}
    MapTile(TileType tile, BuildingType building) : MapTile(tile, building, ItemType::nothing) {}
    MapTile(TileType tile) : MapTile(tile, BuildingType::nothing) {}
};

#endif // TILETYPE_H
