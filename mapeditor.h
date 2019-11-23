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

public:
    explicit MapEditor(QWidget *parent = nullptr);

    int totalTiles() const;

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:

public slots:
};

#endif // MAPEDITOR_H
