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

    const int linecount = tiles_height / 2;
    const double request_width = tiles_width * 2 * std::cos(pi / 6) * edge_length + 1000;
    const double request_height = (linecount + std::sin(pi / 6)) * edge_length * linecount + 100;
    setMinimumSize(QSize(int(request_width), int(request_height)));

    for (int i = 0; i < tiles_height; i++) {
        const double y_start = translation_y + (1 + std::sin(pi / 6)) * edge_length * i + edge_length / 2.0;
        const double x_start = translation_x + (i % 2 == 0 ? 1 : 2) * std::cos(pi / 6) * edge_length;
        for (int j = 0; j < tiles_width; j++) {
            hexCords.push_back(QPointF(x_start + 2 * std::cos(pi / 6) * edge_length * j, y_start));
            mapData.push_back(MapTile(TileType::sea));
        }
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

    switch (tile.tile) {
    case TileType::grass:
        painter.setBrush(QBrush(Qt::green));
        break;
    case TileType::sea:
        painter.setBrush(QBrush(QColor(90, 172, 246)));
        break;
    default:
        painter.setBrush(QBrush(Qt::transparent));
    }

    const QPointF cord2 = QPointF{cord0.x() + 2 * std::cos(pi / 6) * edge_length, cord0.y()};
    const QPointF cord5 = QPointF{cord0.x(), cord0.y() + edge_length};
    const QPointF cord3 = QPointF{cord2.x(), cord5.y()};
    const QPointF cord1 = QPointF{(cord0.x() + cord2.x()) / 2, cord0.y() - std::sin(pi / 6) * edge_length};
    const QPointF cord4 = QPointF{(cord0.x() + cord2.x()) / 2, cord5.y() + std::sin(pi / 6) * edge_length};

    const QPointF points[6] = {
        cord0, cord1, cord2, cord3, cord4, cord5
    };

    painter.drawPolygon(points, 6);
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
    mapData.at(int(tileIndex)) = TileType::grass;
    repaint();
}