#include "viewerwidget.hpp"

#include <QPainter>
#include <QPaintEvent>
#include <QScreen>

static QPixmap chess_pattern()
{
  QPixmap pxm(16, 16);
  pxm.fill(Qt::lightGray);

  QPainter p(&pxm);
  QRect qp(0, 0, pxm.width() / 2, pxm.height() / 2);
  p.fillRect(qp, Qt::gray);
  p.fillRect(qp.translated(qp.width(), qp.height()), Qt::gray);

  return pxm;
}


class ViewerWidget::impl
{
public:
  impl();

  const QImage& image() const { return m_image; }
  void setImage(const QImage& image) { m_image = image; }

  void renderFrame(QPainter* p);

private:
  QImage m_image;
  const QBrush m_chess_b;
};


ViewerWidget::impl::impl()
  : m_chess_b(chess_pattern())
{
}

void ViewerWidget::impl::renderFrame(QPainter* p)
{
  if (m_image.isNull())
    return;

  QSize device_size(p->device()->width(), p->device()->height());

  QPixmap pxm = QPixmap::fromImage(m_image);

  QRect src({0, 0}, pxm.size());
  QRect dst({0, 0}, src.size().scaled(device_size, Qt::KeepAspectRatio));

  QSize scaled_pxm_size = pxm.size() / p->device()->devicePixelRatioF();
  if (scaled_pxm_size.boundedTo(device_size) == scaled_pxm_size)
    dst.setSize(src.size() / p->device()->devicePixelRatioF());

  dst.translate((p->device()->width() - dst.width()) / 2.0, (p->device()->height() - dst.height()) / 2.0);

  p->setPen(Qt::NoPen);
  p->setBrush(m_chess_b);
  p->drawRect(dst);

  pxm.setDevicePixelRatio(p->device()->devicePixelRatioF());
  p->setRenderHint(QPainter::SmoothPixmapTransform);
  p->drawPixmap(dst, pxm, src);
}


ViewerWidget::ViewerWidget(QWidget* parent)
  : QWidget(parent)
  , m_impl(std::make_unique<impl>())
{
}

QSize ViewerWidget::minimumSizeHint() const
{
  QSize hint(400, 300);
  if (!m_impl->image().isNull())
    hint = m_impl->image().size() / devicePixelRatioF();
  // do not allow widget to occupy more that 3/4 of screen space
  hint.scale(hint.boundedTo(screen()->availableSize() * 3/4), Qt::KeepAspectRatio);
  return hint;
}

QSize ViewerWidget::sizeHint() const
{
  return minimumSizeHint();
}

ViewerWidget::~ViewerWidget() = default;

QImage ViewerWidget::image() const
{
  return m_impl->image();
}

qreal ViewerWidget::zoom() const
{
  qreal zoom = 1.0;
  const auto& img = m_impl->image();
  if (!img.isNull()) {
    QSize scaled_size = img.size().scaled(size() * devicePixelRatioF(), Qt::KeepAspectRatio);
    zoom = qMin(1.0, 1.0 * scaled_size.width() / img.size().width());
  }
  return zoom;
}

void ViewerWidget::setImage(const QImage& image)
{
  m_impl->setImage(image);
  updateGeometry();
  update();
}

void ViewerWidget::paintEvent(QPaintEvent* event)
{
  QPainter p(this);
  p.fillRect(rect(), palette().brush(QPalette::Base));
  m_impl->renderFrame(&p);
  event->accept();
}
