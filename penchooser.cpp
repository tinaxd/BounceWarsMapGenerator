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

#include "penchooser.h"

#include <QLabel>
#include <QPushButton>

#include "./tiletype.h"

PenChooser::PenChooser(QWidget *parent, MapEditor *editor) : QWidget(parent), editor(editor), layout(new QGridLayout(this))
{
    // tile pen chooser
    QLabel *penLabel = new QLabel(tr("Tiles"), this);
    layout->addWidget(penLabel, 0, 0);

    auto pen_grass = new QPushButton(this);
    pen_grass->setText(tr("Grass"));
    //pen_grass->setPalette(QPalette(editor->color_tile_grass));
    connect(pen_grass, &QPushButton::released, [=]{
        editor->setTilePen(TileType::grass);
    });
    layout->addWidget(pen_grass, 0, 1);

    auto pen_sea = new QPushButton(this);
    pen_sea->setText("Sea");
    //pen_sea->setPalette(QPalette(editor->color_tile_sea));
    connect(pen_sea, &QPushButton::released, [=]{
        editor->setTilePen(TileType::sea);
    });
    layout->addWidget(pen_sea, 0, 2);

    auto pen_sand = new QPushButton(this);
    pen_sand->setText("Sand");
    connect(pen_sand, &QPushButton::released, [=]{
        editor->setTilePen(TileType::sand);
    });
    layout->addWidget(pen_sand, 0, 3);

    auto pen_brick = new QPushButton(this);
    pen_brick->setText("Brick");
    connect(pen_brick, &QPushButton::released, [=]{
        editor->setTilePen(TileType::brick);
    });
    layout->addWidget(pen_brick, 1, 1);

    auto pen_clay = new QPushButton(this);
    pen_clay->setText("Clay");
    connect(pen_clay, &QPushButton::released, [=]{
        editor->setTilePen(TileType::clay);
    });
    layout->addWidget(pen_clay, 1, 2);

    auto pen_lava = new QPushButton(this);
    pen_lava->setText("Lava");
    connect(pen_lava, &QPushButton::released, [=]{
        editor->setTilePen(TileType::lava);
    });
    layout->addWidget(pen_lava, 1, 3);

    auto pen_rock = new QPushButton(this);
    pen_rock->setText("Rock");
    connect(pen_rock, &QPushButton::released, [=]{
        editor->setTilePen(TileType::rock);
    });
    layout->addWidget(pen_rock, 2, 1);

    // set layout
    setLayout(layout);
}

void PenChooser::setMapEditor(MapEditor *editor)
{
    this->editor = editor;
}


