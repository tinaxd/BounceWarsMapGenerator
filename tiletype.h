/*
    BounceWars map generator
    Copyright (C) 2019 tinaxd

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
