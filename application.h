#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class Application : public QApplication
{
  Q_OBJECT

public:
  using QApplication::QApplication;

signals:
  void fileOpened(const QString& filename);

protected:
  bool event(QEvent* e) override;
};

#endif // APPLICATION_H
