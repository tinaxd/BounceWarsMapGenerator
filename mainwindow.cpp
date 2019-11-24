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
#include <QWindow>
#include <QTextStream>

#include "./mapeditor.h"
#include "./jsonmaptool.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto *central = new QWidget(this);
    auto layout = new QVBoxLayout();

    // editor view
    editor = new MapEditor(this);
    layout->addWidget(editor);

    // toolbar
    penChooser = new PenChooser(this, editor);
    layout->addWidget(penChooser);

    central->setLayout(layout);

    // menubar actions
    QAction *saveJsonAction = new QAction(tr("&Save to json"), this);
    saveJsonAction->setStatusTip("Export the map to a json file");
    connect(saveJsonAction, SIGNAL(triggered()), this, SLOT(saveJson()));

    QAction *readJsonAction = new QAction(tr("&Read from json"), this);
    readJsonAction->setStatusTip("Import map from json");
    connect(readJsonAction, SIGNAL(triggered()), this, SLOT(readJson()));

    // menubar
    menuBar = new QMenuBar(this);

    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(saveJsonAction);
    fileMenu->addAction(readJsonAction);

    // status bar
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    setCentralWidget(central);
}

MainWindow::~MainWindow()
{
}

void MainWindow::saveJson()
{
    QString saveJsonPath = QFileDialog::getSaveFileName(this, tr("Save JSON"), QString(), tr("JSON (*.json *.txt)"));
    if (saveJsonPath == QString())
        return;

    auto mapData = editor->getMapData();
    std::string jsonDump = jsonmaptool::mapToJson(mapData, editor->getTilesWidth(), editor->getTilesHeight());

    QFile file(saveJsonPath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
        return;

    file.write(jsonDump.c_str());

    statusBar->showMessage("Wrote json to file");

    file.close();
}

void MainWindow::readJson()
{
    QString readJsonPath = QFileDialog::getOpenFileName(this, tr("Read JSON"), QString(), tr("JSON (*.json *.txt"));
    if (readJsonPath == QString())
        return;
    QFile file(readJsonPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream stream(&file);
    std::string jsonData;
    {
        QString tmp = stream.readAll();
        jsonData = tmp.toUtf8().constData();
    }

    int width, height;
    std::vector<MapTile> mapData = jsonmaptool::jsonToMap(jsonData, &width, &height);

    editor->setTilesWidth(width);
    editor->setTilesHeight(height);
    editor->setMapData(std::move(mapData));
}
