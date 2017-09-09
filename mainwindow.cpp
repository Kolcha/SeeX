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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QImageReader>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  img_reader_ = new QImageReader();
}

MainWindow::~MainWindow()
{
  delete img_reader_;
  delete ui;
}

void MainWindow::loadFile(const QString& filename)
{
  if (tryLoadFile(filename)) {
    QFileInfo fi(filename);
    QDir::setCurrent(fi.absolutePath());
    QDir cur_dir = QDir::current();
    cur_dir.setFilter(QDir::Files | QDir::Hidden | QDir::Readable);
    cur_dir.setSorting(QDir::Name | QDir::IgnoreCase | QDir::LocaleAware);
    files_ = cur_dir.entryList();
    cur_index_ = files_.indexOf(fi.fileName());
  }
}

void MainWindow::on_actionOpen_triggered()
{
  QString filename = QFileDialog::getOpenFileName(this);
  if (!filename.isEmpty()) loadFile(filename);
}

void MainWindow::on_actionSave_triggered()
{
    //
}

void MainWindow::on_actionCopy_triggered()
{
    //
}

void MainWindow::on_actionPaste_triggered()
{
    //
}

void MainWindow::on_actionNextFile_triggered()
{
  Q_ASSERT(!files_.isEmpty());
  Q_ASSERT(cur_index_ < files_.size() - 1);
  while (++cur_index_ < files_.size() && !tryLoadFile(files_[cur_index_]));
}

void MainWindow::on_actionPreviousFile_triggered()
{
  Q_ASSERT(!files_.isEmpty());
  Q_ASSERT(cur_index_ > 0);
  while (--cur_index_ >= 0 && !tryLoadFile(files_[cur_index_]));
}

void MainWindow::on_actionFirstFile_triggered()
{
  Q_ASSERT(!files_.isEmpty());
  cur_index_ = 0;
  while (++cur_index_ < files_.size() && !tryLoadFile(files_[cur_index_]));
}

void MainWindow::on_actionLastFile_triggered()
{
  Q_ASSERT(!files_.isEmpty());
  cur_index_ = files_.size() - 1;
  while (--cur_index_ >= 0 && !tryLoadFile(files_[cur_index_]));
}

void MainWindow::on_actionNextFrame_triggered()
{
    //
}

void MainWindow::on_actionPreviousFrame_triggered()
{
    //
}

void MainWindow::on_actionZoon_In_triggered()
{
    //
}

void MainWindow::on_actionZoom_Out_triggered()
{
    //
}

void MainWindow::on_actionNormal_Size_triggered()
{
    //
}

void MainWindow::on_actionFit_to_Window_triggered()
{
  //
}

bool MainWindow::tryLoadFile(const QString& file)
{
  img_reader_->setFileName(file);
  img_reader_->setAutoDetectImageFormat(true);
  img_reader_->setAutoTransform(true);
  if (img_reader_->canRead()) {
    QImage img = img_reader_->read();
    if (!img.isNull()) {
      ui->label->setPixmap(QPixmap::fromImage(img));
      setWindowFilePath(file);
      return true;
    }
  }
  return false;
}
