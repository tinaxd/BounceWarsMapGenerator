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

#include <iostream>

std::string jsonmaptool::mapToJson(const std::vector<MapTile> &mapData, int width, int height)
{
    using namespace std;

    Json j;

    j["id"] = 1;
    j["mapType"] = 3;

    vector<vector<map<string, int>>> top;
    for (int i = height; i --> 0; ) {
        vector<map<string, int>> horizontal;
        for (int k = 0; k < width; k++) {
            const MapTile &data = mapData.at(size_t(i * width + k));
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

std::vector<MapTile> jsonmaptool::jsonToMap(std::string jsonData, int *width, int *height)
{
    using namespace std;

    size_t jWidth, jHeight;
    std::vector<MapTile> ret;

    try {
        Json json{Json::parse(jsonData)};
        vector<vector<map<string, int>>> top = json["mapData"];
        jHeight = top.size();
        if (jHeight == 0)
            return std::vector<MapTile>();
        jWidth = top.at(0).size();
        if (jWidth == 0)
            return std::vector<MapTile>();

        cout << jHeight << endl;
        for (size_t i = jHeight; i --> 0; ) {
            for (size_t j = 0; j < jWidth; j++) {

                map<string, int> tile = top[i][j];

                MapTile mt{TileType(int(tile.at("type")))};

                if (auto building = tile.find("buildingType"); building != tile.end()) {
                    mt.building = BuildingType(int(building->second));
                }

                ret.push_back(mt);
                // TODO item support
            }
        }

        *width  = int(jWidth);
        *height = int(jHeight);
    } catch (Json::type_error &e) {
        cerr << e.what() << endl;
    }

    return ret;
}
