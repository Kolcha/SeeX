#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QWindow>

#include "fileprovider.h"
#include "frameprovider.h"
#include "statuslabel.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  del_no_confirm_(false)
{
  ui->setupUi(this);

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
  connect(fr_provider_, &FrameProvider::currentFrameChanged, ui->viewer, &ViewerWidget::setImage);
  connect(fr_provider_, &FrameProvider::currentFrameChanged, this, &MainWindow::updateNavigationActions);
  connect(fr_provider_, &FrameProvider::currentFrameChanged, this, &MainWindow::updateStatusBar);

  st_file_ = new StatusLabel(":/images/status/folder.svg", "0/0");
  st_frame_ = new StatusLabel(":/images/status/frame.svg", "0/0");
  st_zoom_ = new StatusLabel(":/images/status/zoom.svg", "100 %");
  st_resolution_ = new StatusLabel(":/images/status/resolution.svg", "0x0");
  st_format_ = new StatusLabel(":/images/status/file.svg", "-");
  ui->statusBar->addWidget(st_file_);
  ui->statusBar->addWidget(st_frame_);
  ui->statusBar->addPermanentWidget(st_format_);
  ui->statusBar->addPermanentWidget(st_resolution_);
  ui->statusBar->addPermanentWidget(st_zoom_);
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

void MainWindow::changeEvent(QEvent* event)
{
  if (event->type() == QEvent::WindowStateChange) {
    ui->statusBar->setVisible(windowState() != Qt::WindowFullScreen);
  }
  QMainWindow::changeEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
  updateStatusBar();
  QMainWindow::resizeEvent(event);
}

void MainWindow::on_actionOpen_triggered()
{
  QString filename = QFileDialog::getOpenFileName(this);
  if (!filename.isEmpty()) openFile(filename);
}

void MainWindow::on_actionDelete_triggered()
{
  if (!del_no_confirm_) {
    QMessageBox::StandardButton btn = QMessageBox::question(
          this, tr("Delete file"),
          tr("Are you sure do you want to delete this file? This is can not be undone."),
          QMessageBox::YesToAll | QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (btn == QMessageBox::No) return;
    Q_ASSERT(btn == QMessageBox::YesToAll || btn == QMessageBox::Yes);
    del_no_confirm_ = btn == QMessageBox::YesToAll;
  }
  fi_provider_->deleteCurrentFile();
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
  ui->actionDelete->setEnabled(!ui->viewer->image().isNull());
}

void MainWindow::updateStatusBar()
{
  st_file_->setText(QString("%1/%2").arg(fi_provider_->currentIndex() + 1).arg(fi_provider_->filesCount()));
  st_frame_->setText(QString("%1/%2").arg(fr_provider_->currentIndex() + 1).arg(fr_provider_->framesCount()));
  QImage cur_img = ui->viewer->image();
  if (cur_img.isNull()) {
    st_zoom_->setText("100 %");
    st_format_->setText("-");
  } else {
    st_zoom_->setText(QString("%1 %").arg(qRound(100 * ui->viewer->zoom())));
    st_format_->setText(fr_provider_->fileFormat());
  }
  st_resolution_->setText(QString("%1x%2").arg(cur_img.width()).arg(cur_img.height()));
}
