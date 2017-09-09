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
#include <QFileInfo>
#include <QImageReader>

#include "fileprovider.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->scrollArea->setBackgroundRole(QPalette::Dark);

  ui->actionOpen->setShortcut(QKeySequence::Open);

  img_reader_ = new QImageReader();
  provider_ = new FileProvider(this);
  connect(ui->actionNextFile, &QAction::triggered, provider_, &FileProvider::nextFile);
  connect(ui->actionPreviousFile, &QAction::triggered, provider_, &FileProvider::previousFile);
  connect(ui->actionFirstFile, &QAction::triggered, provider_, &FileProvider::firstFile);
  connect(ui->actionLastFile, &QAction::triggered, provider_, &FileProvider::lastFile);
  connect(provider_, &FileProvider::currentFileChanged, this, &MainWindow::loadImage);
}

MainWindow::~MainWindow()
{
  delete img_reader_;
  delete ui;
}

void MainWindow::openFile(const QString& filename)
{
  QFileInfo fi(filename);
  provider_->scanDir(fi.absolutePath());
  provider_->setCurrentFile(fi.absoluteFilePath());
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
  if (!cur_image_.isNull()) updateImage();
  QMainWindow::resizeEvent(event);
}

void MainWindow::loadImage(const QString& filename)
{
  if (filename.isEmpty()) return;

  img_reader_->setFileName(filename);
  img_reader_->setAutoTransform(true);
  img_reader_->setDecideFormatFromContent(true);

  if (img_reader_->canRead()) {
    cur_frame_ = 0;
    updateNavigationActions();
    cur_image_ = img_reader_->read();
    updateImage();
    setWindowFilePath(filename);
  }
}

void MainWindow::on_actionOpen_triggered()
{
  QString filename = QFileDialog::getOpenFileName(this);
  if (!filename.isEmpty()) openFile(filename);
}

void MainWindow::on_actionNextFrame_triggered()
{
  Q_ASSERT(cur_frame_ < img_reader_->imageCount());
  loadFrame(++cur_frame_);
}

void MainWindow::on_actionPreviousFrame_triggered()
{
  Q_ASSERT(cur_frame_ > 0);
  loadFrame(--cur_frame_);
}

void MainWindow::loadFrame(int index)
{
  if (img_reader_->jumpToImage(index) && img_reader_->canRead()) {
    cur_image_ = img_reader_->read();
    if (!cur_image_.isNull()) updateImage();
  }
  updateNavigationActions();
}

void MainWindow::updateNavigationActions()
{
  ui->actionNextFile->setDisabled(provider_->currentIndex() == provider_->filesCount() - 1);
  ui->actionPreviousFile->setDisabled(provider_->currentIndex() == 0);
  ui->actionFirstFile->setEnabled(ui->actionPreviousFile->isEnabled());
  ui->actionLastFile->setEnabled(ui->actionNextFile->isEnabled());
  int frames_count = img_reader_->imageCount();
  ui->actionNextFrame->setDisabled(frames_count <= 1 || cur_frame_ == frames_count - 1);
  ui->actionPreviousFrame->setDisabled(frames_count <= 1 || cur_frame_ == 0);
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
