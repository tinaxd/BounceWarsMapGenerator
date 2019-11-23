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

#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QWidget>

#include <vector>

#include "./tiletype.h"

class MapEditor : public QWidget
{
    Q_OBJECT

    int tiles_width;
    int tiles_height;

    double edge_length;

    double translation_x;
    double translation_y;

    std::vector<QPointF> hexCords;
    std::vector<MapTile> mapData;

    QPointF getCoordinateOfTileIndex(int tileIndex) const;
    int getTileIndexOfCord(QPointF cord) const;

    void drawTileIndex(QPainter& painter, int tileIndex);

    int penType = 0; // 0: Tile, 1: Building, 2: Item
    TileType tilePen = TileType::grass;
    BuildingType buildingPen = BuildingType::nothing;
    ItemType itemPen = ItemType::nothing;

public:
    explicit MapEditor(QWidget *parent = nullptr);

    int totalTiles() const;

    QColor color_tile_grass;
    QColor color_tile_sea;

    void setTilePen(TileType tileType);
    void setBuildingPen(BuildingType buildingType);
    void setItemPen(ItemType itemType);

    const std::vector<MapTile>& getMapData() const;

    int get_tiles_width() const;
    int get_tiles_height() const;

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:

public slots:
};

#endif // MAPEDITOR_H
