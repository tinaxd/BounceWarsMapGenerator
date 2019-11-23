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

#include "mainwindow.h"

#include <QVBoxLayout>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QFileDialog>

#include "./mapeditor.h"
#include "./jsonmaptool.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    auto layout = new QVBoxLayout();

    // editor view
    editor = new MapEditor(this);
    layout->addWidget(editor);

    setLayout(layout);

    // menubar actions
    QAction *saveJsonAction = new QAction(tr("&Save to json"), this);
    saveJsonAction->setStatusTip("Export the map to a json file");
    connect(saveJsonAction, SIGNAL(triggered()), this, SLOT(saveJson()));

    // menubar
    menuBar = new QMenuBar(this);

    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(saveJsonAction);

    // status bar
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
}

MainWindow::~MainWindow()
{
}

void MainWindow::saveJson()
{
    QString saveJsonPath = QFileDialog::getSaveFileName(this, tr("Save JSON"), QString(), tr("JSON (*.json, *.txt)"));

    auto mapData = editor->getMapData();
    std::string jsonDump = jsonmaptool::mapToJson(mapData, editor->get_tiles_width(), editor->get_tiles_height());

    QFile file(saveJsonPath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
        return;

    file.write(jsonDump.c_str());

    statusBar->showMessage("Wrote json to file");
}

