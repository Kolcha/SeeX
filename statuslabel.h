#ifndef STATUSLABEL_H
#define STATUSLABEL_H

#include <QWidget>
#include <QIcon>

class QLabel;

class StatusLabel : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
  Q_PROPERTY(QString text READ text WRITE setText)

public:
  explicit StatusLabel(QWidget* parent = nullptr);
  StatusLabel(const QIcon& icn, const QString& txt, QWidget* parent = nullptr);

  QIcon icon() const;
  QString text() const;

public slots:
  void setIcon(const QIcon& icn);
  void setText(const QString& txt);

protected:
  void changeEvent(QEvent* event) override;

private:
  QIcon icon_;
  const int icon_size_ = 16;

  QLabel* icon_lbl_;
  QLabel* text_lbl_;
};

#endif // STATUSLABEL_H
