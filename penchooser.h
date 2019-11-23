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

#ifndef PENCHOOSER_H
#define PENCHOOSER_H

#include <QWidget>
#include <QGridLayout>

#include "./mapeditor.h"

class PenChooser : public QWidget
{
    Q_OBJECT

    MapEditor *editor;

    QGridLayout *layout;

public:
    explicit PenChooser(QWidget *parent, MapEditor *editor);

    void setMapEditor(MapEditor *editor);

signals:

public slots:
};

#endif // PENCHOOSER_H
