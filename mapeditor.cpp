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

#include "mapeditor.h"

#include <QPainter>
#include <QMouseEvent>

#include <cmath>
#include <iostream>
#include <limits>

constexpr double pi = 3.14159265358979323846;

MapEditor::MapEditor(QWidget *parent) : QWidget(parent)
{
    tiles_width = 18;
    tiles_height = 8;
    edge_length = 30;
    translation_x = 50;
    translation_y = 50;

    color_tile_grass = Qt::green;
    color_tile_sea = QColor::fromRgb(90, 172, 246);
    color_tile_sand = QColor::fromRgb(223, 210, 185);
    color_tile_brick = QColor::fromRgb(255, 137, 0);
    color_tile_clay = QColor::fromRgb(118, 114, 109);
    color_tile_lava = Qt::red;
    color_tile_rock = Qt::black;

    color_building_tree = QColor::fromRgb(13, 37, 27);
    color_building_stone = QColor::fromRgb(130, 130, 132);

    updateSizeRequest();
  
    updateHexCords();

    for (int i = 0; i < totalTiles(); i++) {
        mapData.emplace_back(MapTile{TileType::grass});
    }
}

void MapEditor::paintEvent(QPaintEvent *)
{
    QPainter painter{this};

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));

    painter.translate(translation_x, translation_y);

    /*
    QPointF finalup;
    for (int i = 0; i < tiles_height*2; i++) {
        const int linecount = i / 2;
        const double y_start = (1 + std::sin(pi / 6)) * edge_length * linecount;
        const double x_start = (i / 2) % 2 == 0 ? 0 : std::cos(pi / 6) * edge_length;
        QPointF lastpoint = QPointF{x_start, y_start};
        if (i % 2 == 0) {
            for(int j = 0; j < tiles_width; j++) {
                const double y_next = lastpoint.y() - std::sin(pi / 6) * edge_length;
                const double x_next = lastpoint.x() + std::cos(pi / 6) * edge_length;
                const QPointF nextpoint = QPointF{x_next, y_next};
                painter.drawLine(lastpoint, nextpoint);

                const double x_next2 = lastpoint.x() + 2 * std::cos(pi / 6) * edge_length;
                const double y_next2 = lastpoint.y();
                const QPointF nextpoint2 = QPointF{x_next2, y_next2};
                painter.drawLine(nextpoint, nextpoint2);

                lastpoint = nextpoint2;
            }
        } else {
            for (int j = 0; j <= tiles_width; j++) {
                const QPointF nextpoint = QPointF{lastpoint.x(), lastpoint.y() + edge_length};
                painter.drawLine(lastpoint, nextpoint);

                lastpoint = QPointF{lastpoint.x() + 2 * std::cos(pi / 6) * edge_length, lastpoint.y()};
            }
            const auto final1 = QPointF{x_start, y_start + edge_length};
            const auto final2 = QPointF{final1.x() + std::cos(pi / 6) * edge_length, final1.y() + std::sin(pi / 6) * edge_length};
            painter.drawLine(final1, final2);
            finalup = final2;
        }
    }

    const double x_next = finalup.x() + std::cos(pi / 6) * edge_length;
    const double y_next = finalup.y() - std::sin(pi / 6) * edge_length;
    const QPointF finalup_next = QPointF{x_next, y_next};
    painter.drawLine(finalup, finalup_next);
    QPointF lastpoint = finalup_next;
    for(int j = 0; j < tiles_width-1; j++) {
        const double y_next = lastpoint.y() + std::sin(pi / 6) * edge_length;
        const double x_next = lastpoint.x() + std::cos(pi / 6) * edge_length;
        const QPointF nextpoint = QPointF{x_next, y_next};
        painter.drawLine(lastpoint, nextpoint);

        const double x_next2 = lastpoint.x() + 2 * std::cos(pi / 6) * edge_length;
        const double y_next2 = lastpoint.y();
        const QPointF nextpoint2 = QPointF{x_next2, y_next2};
        painter.drawLine(nextpoint, nextpoint2);

        lastpoint = nextpoint2;
    }*/

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
    //painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::SquareCap));
    for (size_t _tileIndex = 0; _tileIndex < mapData.size(); _tileIndex++) {
        drawTileIndex(painter, int(_tileIndex));
        //painter.drawPoint(getCoordinateOfTileIndex(int(_tileIndex)));
    }

    /*painter.translate(-translation_x, -translation_y);
    painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::SquareCap));
    for (const QPointF& center : hexCords) {
        painter.drawPoint(center);
    }*/
};

void MapEditor::drawTileIndex(QPainter& painter, int tileIndex)
{
    const MapTile& tile = mapData.at(size_t(tileIndex));
    const QPointF  cord0 = getCoordinateOfTileIndex(tileIndex);

    // Draw tile
    QColor *color;
    switch (tile.tile) {
    case TileType::grass:
        color = &color_tile_grass;
        break;
    case TileType::sea:
        color = &color_tile_sea;
        break;
    case TileType::sand:
        color = &color_tile_sand;
        break;
    case TileType::brick:
        color = &color_tile_brick;
        break;
    case TileType::clay:
        color = &color_tile_clay;
        break;
    case TileType::lava:
        color = &color_tile_lava;
        break;
    case TileType::rock:
        color = &color_tile_rock;
        break;
    }
    painter.setBrush(QBrush{*color});

    const QPointF cord2 = QPointF{cord0.x() + 2 * std::cos(pi / 6) * edge_length, cord0.y()};
    const QPointF cord5 = QPointF{cord0.x(), cord0.y() + edge_length};
    const QPointF cord3 = QPointF{cord2.x(), cord5.y()};
    const QPointF cord1 = QPointF{(cord0.x() + cord2.x()) / 2, cord0.y() - std::sin(pi / 6) * edge_length};
    const QPointF cord4 = QPointF{(cord0.x() + cord2.x()) / 2, cord5.y() + std::sin(pi / 6) * edge_length};

    const QPointF points[6] = {
        cord0, cord1, cord2, cord3, cord4, cord5
    };

    painter.drawPolygon(points, 6);


    // Draw building
    {
        QColor *bColor;
        switch (tile.building) {
        case BuildingType::nothing:
            goto DRAWEND;
        case BuildingType::forest:
            bColor = &color_building_tree;
            break;
        case BuildingType::stones1:
        case BuildingType::stones2:
        case BuildingType::stones3:
            bColor = &color_building_stone;
            break;
        }

        const QPointF center = (cord0 + cord3) / 2;
        const double radius = edge_length * std::sin(pi / 3) / 2;
        const QRectF rect = QRectF{center - QPointF{radius, radius}, QSizeF{2 * radius, 2 * radius}};

        painter.setBrush(QBrush{*bColor});
        painter.drawEllipse(rect);
    }

    DRAWEND:

    return;
}

int MapEditor::totalTiles() const
{
    return tiles_width * tiles_height;
}

QPointF MapEditor::getCoordinateOfTileIndex(int tileIndex) const
{
    const int row = tileIndex / tiles_width;
    const int col = tileIndex % tiles_width;

    const double y = (1 + std::sin(pi / 6)) * edge_length * row;
    const double x = (row % 2 == 0 ? 0 : std::cos(pi / 6) * edge_length) + 2 * std::cos(pi / 6) * edge_length * col;
    return QPointF{x, y};
}

int MapEditor::getTileIndexOfCord(QPointF cord) const
{
    double mindist = std::numeric_limits<double>::max();
    size_t minIndex = 0;
    for (size_t i = 0; i < hexCords.size(); i++) {
        const QPointF& hex = hexCords.at(i);
        double dist = std::sqrt(std::pow(cord.x() - hex.x(), 2) + std::pow(cord.y() - hex.y(), 2));
        if (dist < mindist) {
            mindist = dist;
            minIndex = i;
        }
    }
    int tileIndex = mindist <= edge_length ? int(minIndex) : -1;
    return tileIndex;
}

void MapEditor::mousePressEvent(QMouseEvent *event)
{
    int tileIndex = getTileIndexOfCord(QPointF{qreal(event->x()), qreal(event->y())});
    std::cout << tileIndex << std::endl;
    if (tileIndex == -1)
        return;

    MapTile &editing = mapData.at(size_t(tileIndex));
    switch (penType) {
    case 0: // TilePen
        editing = MapTile{tilePen, editing.building, editing.item};
        break;
    case 1: // Building Pen
        editing = MapTile{editing.tile, buildingPen, editing.item};
        break;
    case 2:
        editing = MapTile{editing.tile, editing.building, itemPen};
        break;
    }

    repaint();
}

void MapEditor::setTilePen(TileType tileType)
{
    tilePen = tileType;
    penType = 0;
}

void MapEditor::setBuildingPen(BuildingType buildingType)
{
    buildingPen = buildingType;
    penType = 1;
}

void MapEditor::setItemPen(ItemType itemType)
{
    itemPen = itemType;
    penType = 2;
}

const std::vector<MapTile>& MapEditor::getMapData() const
{
    return mapData;
}

int MapEditor::getTilesWidth() const
{
    return tiles_width;
}

int MapEditor::getTilesHeight() const
{
    return tiles_height;
}

void MapEditor::setTilesWidth(int width)
{
    this->tiles_width = width;
    updateSizeRequest();
    updateHexCords();
    // TODO extend or shrink previous mapData
}

void MapEditor::setTilesHeight(int height)
{
    this->tiles_height = height;
    updateSizeRequest();
    updateHexCords();
    // TODO extend or shrink previous mapData
}

void MapEditor::setMapData(std::vector<MapTile> &&mapData)
{
    if (size_t(tiles_height * tiles_width) != mapData.size()) {
        std::cerr << "Corrupted map data" << std::endl;
        return;
    }

    this->mapData = std::move(mapData);
}

void MapEditor::updateSizeRequest()
{
    const int linecount = tiles_height / 2;
    const double request_width = tiles_width * 2 * std::cos(pi / 6) * edge_length + 100;
    const double request_height = (linecount + std::sin(pi / 6)) * edge_length * linecount + 10;
    setMinimumSize(QSize(int(request_width), int(request_height)));
}

void MapEditor::updateHexCords()
{
    hexCords.clear();
    for (int i = 0; i < tiles_height; i++) {
        const double y_start = translation_y + (1 + std::sin(pi / 6)) * edge_length * i + edge_length / 2.0;
        const double x_start = translation_x + (i % 2 == 0 ? 1 : 2) * std::cos(pi / 6) * edge_length;
        for (int j = 0; j < tiles_width; j++) {
            hexCords.push_back(QPointF(x_start + 2 * std::cos(pi / 6) * edge_length * j, y_start));
        }
    }
}
