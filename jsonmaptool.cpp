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

#include "jsonmaptool.h"

#include "ext/json.hpp"
using Json = nlohmann::json;

std::string jsonmaptool::mapToJson(const std::vector<MapTile> &mapData, int width, int height)
{
    using namespace std;

    Json j;

    j["id"] = 1;
    j["mapType"] = 3;

    vector<vector<map<string, int>>> top;
    for (int i = 0; i < height; i++) {
        vector<map<string, int>> horizontal;
        for (int j = 0; j < width; j++) {
            const MapTile &data = mapData.at(size_t(i * height + j));
            map<string, int> tile;

            tile.insert(make_pair("type", int(data.tile)));

            if (data.building != BuildingType::nothing) {
                tile.insert(make_pair("buildingType", int(data.building)));
            }

            // TODO item support

            horizontal.push_back(std::move(tile));
        }
        top.push_back(std::move(horizontal));
    }

    j["mapData"] = top;

    return j.dump();
}
