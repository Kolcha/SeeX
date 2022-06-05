#ifndef STATUSLABEL_H
#define STATUSLABEL_H

#include <QWidget>

class QLabel;

class StatusLabel : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QPixmap icon READ icon WRITE setIcon)
  Q_PROPERTY(QString text READ text WRITE setText)

public:
  explicit StatusLabel(QWidget* parent = nullptr);
  StatusLabel(const QPixmap& pxm, const QString& txt, QWidget* parent = nullptr);
  StatusLabel(const QString& pxm, const QString& txt, QWidget* parent = nullptr);

  QPixmap icon() const;
  QString text() const;

public slots:
  void setIcon(const QPixmap& icn);
  void setIcon(const QString& icn);
  void setText(const QString& txt);

private:
  QLabel* icon_lbl_;
  QLabel* text_lbl_;
};

#endif // STATUSLABEL_H
