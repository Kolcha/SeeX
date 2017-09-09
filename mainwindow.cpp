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

  ui->scrollArea->setBackgroundRole(QPalette::Dark);

  ui->actionOpen->setShortcut(QKeySequence::Open);
  ui->actionSave->setShortcut(QKeySequence::Save);

  ui->actionCopy->setShortcut(QKeySequence::Copy);
  ui->actionPaste->setShortcut(QKeySequence::Paste);

  ui->actionZoomIn->setShortcut(QKeySequence::ZoomIn);
  ui->actionZoomOut->setShortcut(QKeySequence::ZoomOut);

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
    cur_dir.setFilter(QDir::Files | QDir::Readable);
    cur_dir.setSorting(QDir::Name | QDir::IgnoreCase | QDir::LocaleAware);
    files_ = cur_dir.entryList();
    cur_index_ = files_.indexOf(fi.fileName());
    ui->actionFirstFile->setEnabled(true);
    ui->actionLastFile->setEnabled(true);
  }
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
  if (!cur_image_.isNull()) updateImage();
  QMainWindow::resizeEvent(event);
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
  while (cur_index_ < files_.size() && !tryLoadFile(files_[cur_index_])) ++cur_index_;
}

void MainWindow::on_actionLastFile_triggered()
{
  Q_ASSERT(!files_.isEmpty());
  cur_index_ = files_.size() - 1;
  while (cur_index_ >= 0 && !tryLoadFile(files_[cur_index_])) --cur_index_;
}

void MainWindow::on_actionNextFrame_triggered()
{
    //
}

void MainWindow::on_actionPreviousFrame_triggered()
{
    //
}

void MainWindow::on_actionZoomIn_triggered()
{
    //
}

void MainWindow::on_actionZoomOut_triggered()
{
    //
}

void MainWindow::on_actionNormalSize_triggered()
{
    //
}

bool MainWindow::tryLoadFile(const QString& file)
{
  updateNavigationActions();
  img_reader_->setFileName(file);
  img_reader_->setAutoDetectImageFormat(true);
  img_reader_->setAutoTransform(true);
  if (img_reader_->canRead()) {
    cur_image_ = img_reader_->read();
    if (!cur_image_.isNull()) {
      updateImage();
      setWindowFilePath(file);
      return true;
    }
  }
  return false;
}

void MainWindow::updateNavigationActions()
{
  ui->actionNextFile->setDisabled(cur_index_ == files_.size() - 1);
  ui->actionPreviousFile->setDisabled(cur_index_ == 0);
  ui->actionFirstFile->setEnabled(ui->actionPreviousFile->isEnabled());
  ui->actionLastFile->setEnabled(ui->actionNextFile->isEnabled());
}

void MainWindow::updateImage()
{
  if (cur_image_.width() > ui->label->width() || cur_image_.height() > ui->label->height()) {
    QImage img = cur_image_.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(img));
  } else {
    ui->label->setPixmap(QPixmap::fromImage(cur_image_));
  }
}
