#pragma once

#include <QWidget>
#include <QImage>
#include <memory>

class ViewerWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ViewerWidget(QWidget* parent = nullptr);
  ~ViewerWidget();

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

  QImage image() const;

  qreal zoom() const;

public slots:
  void setImage(const QImage& image);

protected:
  void paintEvent(QPaintEvent* event) override;

private:
  class impl;
  std::unique_ptr<impl> m_impl;
};
