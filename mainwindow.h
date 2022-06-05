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
  void changeEvent(QEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;

private slots:
  void on_actionOpen_triggered();
  void on_actionDelete_triggered();

private:
  void updateNavigationActions();
  void updateStatusBar();
  void handleEscKey();

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
