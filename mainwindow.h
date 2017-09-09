/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2017  Nick Korotysh <nick.korotysh@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class FileProvider;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void openFile(const QString& filename);

protected:
  void resizeEvent(QResizeEvent* event);

private slots:
  void loadImage(const QString& filename);

  void on_actionOpen_triggered();
  void on_actionSave_triggered();

  void on_actionCopy_triggered();
  void on_actionPaste_triggered();

  void on_actionNextFrame_triggered();
  void on_actionPreviousFrame_triggered();

  void on_actionZoomIn_triggered();
  void on_actionZoomOut_triggered();
  void on_actionNormalSize_triggered();

private:
  void loadFrame(int index);
  void updateNavigationActions();
  void updateImage();

private:
  Ui::MainWindow *ui;

  FileProvider* provider_;
  QImageReader* img_reader_;
  QImage cur_image_;
  int cur_frame_;
};

#endif // MAINWINDOW_H
