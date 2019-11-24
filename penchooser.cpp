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

    // building pen chooser
    QLabel *buildingLabel = new QLabel(tr("Buildings"), this);
    layout->addWidget(buildingLabel, 3, 0);

    auto pen_b_nothing = new QPushButton(this);
    pen_b_nothing->setText(tr("No Building"));
    connect(pen_b_nothing, &QPushButton::released, [=]{
        editor->setBuildingPen(BuildingType::nothing);
    });
    layout->addWidget(pen_b_nothing, 3, 1);

    auto pen_forest = new QPushButton(this);
    pen_forest->setText(tr("Forest"));
    connect(pen_forest, &QPushButton::released, [=]{
        editor->setBuildingPen(BuildingType::forest);
    });
    layout->addWidget(pen_forest, 3, 2);

    auto pen_stone1 = new QPushButton(this);
    pen_stone1->setText("Stone1");
    connect(pen_stone1, &QPushButton::released, [=]{
        editor->setBuildingPen(BuildingType::stones1);
    });
    layout->addWidget(pen_stone1, 3, 3);

    auto pen_stone2 = new QPushButton(this);
    pen_stone2->setText("Stone2");
    connect(pen_stone2, &QPushButton::released, [=]{
        editor->setBuildingPen(BuildingType::stones2);
    });
    layout->addWidget(pen_stone2, 4, 1);

    auto pen_stone3 = new QPushButton(this);
    pen_stone3->setText("Stone3");
    connect(pen_stone3, &QPushButton::released, [=]{
        editor->setBuildingPen(BuildingType::stones3);
    });
    layout->addWidget(pen_stone3, 4, 2);

    // set layout
    setLayout(layout);
}

void PenChooser::setMapEditor(MapEditor *editor)
{
    this->editor = editor;
}


