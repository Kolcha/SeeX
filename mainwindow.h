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
class FrameProvider;
class StatusLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

public slots:
  void openFile(const QString& filename);

protected:
  void resizeEvent(QResizeEvent* event);

private slots:
  void on_actionOpen_triggered();
  void on_actionDelete_triggered();

private:
  void updateNavigationActions();
  void updateStatusBar();

private:
  Ui::MainWindow* ui;

  FileProvider* fi_provider_;
  FrameProvider* fr_provider_;

  StatusLabel* st_file_;
  StatusLabel* st_frame_;
  StatusLabel* st_zoom_;
  StatusLabel* st_resolution_;
  StatusLabel* st_format_;

  bool del_no_confirm_;
};

#endif // MAINWINDOW_H
