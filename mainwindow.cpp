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

#include "fileprovider.h"
#include "frameprovider.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->scrollArea->setBackgroundRole(QPalette::Dark);

  ui->actionOpen->setShortcut(QKeySequence::Open);

  fi_provider_ = new FileProvider(this);
  connect(ui->actionNextFile, &QAction::triggered, fi_provider_, &FileProvider::nextFile);
  connect(ui->actionPreviousFile, &QAction::triggered, fi_provider_, &FileProvider::previousFile);
  connect(ui->actionFirstFile, &QAction::triggered, fi_provider_, &FileProvider::firstFile);
  connect(ui->actionLastFile, &QAction::triggered, fi_provider_, &FileProvider::lastFile);

  fr_provider_ = new FrameProvider(this);
  connect(fi_provider_, &FileProvider::currentFileChanged, fr_provider_, &FrameProvider::setFileName);
  connect(ui->actionNextFrame, &QAction::triggered, fr_provider_, &FrameProvider::nextFrame);
  connect(ui->actionPreviousFrame, &QAction::triggered, fr_provider_, &FrameProvider::previousFrame);
  connect(fr_provider_, &FrameProvider::fileNameChanged, this, &MainWindow::setWindowFilePath);
  connect(fr_provider_, &FrameProvider::currentFrameChanged, this, &MainWindow::displayImage);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::openFile(const QString& filename)
{
  QFileInfo fi(filename);
  fi_provider_->scanDir(fi.absolutePath());
  fi_provider_->setCurrentFile(fi.absoluteFilePath());
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
  if (!cur_image_.isNull()) updateImage();
  QMainWindow::resizeEvent(event);
}

void MainWindow::displayImage(const QImage& img)
{
  cur_image_ = img;
  updateImage();
  updateNavigationActions();
}

void MainWindow::on_actionOpen_triggered()
{
  QString filename = QFileDialog::getOpenFileName(this);
  if (!filename.isEmpty()) openFile(filename);
}

void MainWindow::updateNavigationActions()
{
  ui->actionNextFile->setDisabled(fi_provider_->currentIndex() == fi_provider_->filesCount() - 1);
  ui->actionPreviousFile->setDisabled(fi_provider_->currentIndex() == 0);
  ui->actionFirstFile->setEnabled(ui->actionPreviousFile->isEnabled());
  ui->actionLastFile->setEnabled(ui->actionNextFile->isEnabled());
  int frames_count = fr_provider_->framesCount();
  ui->actionNextFrame->setDisabled(frames_count <= 1 || fr_provider_->currentIndex() == frames_count - 1);
  ui->actionPreviousFrame->setDisabled(frames_count <= 1 || fr_provider_->currentIndex() == 0);
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
