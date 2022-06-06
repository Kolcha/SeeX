#include "statuslabel.h"

#include <QEvent>
#include <QLabel>
#include <QHBoxLayout>
#include <QIcon>

StatusLabel::StatusLabel(QWidget* parent) : QWidget(parent)
{
  icon_lbl_ = new QLabel;
  text_lbl_ = new QLabel;
  QHBoxLayout* l = new QHBoxLayout;
  l->setContentsMargins(0, 0, 0, 0);
  l->setSpacing(4);
  l->addWidget(icon_lbl_);
  l->addWidget(text_lbl_);
  setLayout(l);
}

StatusLabel::StatusLabel(const QIcon& icn, const QString& txt, QWidget* parent) : StatusLabel(parent)
{
  setIcon(icn);
  setText(txt);
}

QIcon StatusLabel::icon() const
{
  return icon_;
}

QString StatusLabel::text() const
{
  return text_lbl_->text();
}

void StatusLabel::setIcon(const QIcon& icn)
{
  icon_ = icn;
  icon_lbl_->setPixmap(icn.pixmap(icon_size_));
}

void StatusLabel::setText(const QString& txt)
{
  text_lbl_->setText(txt);
}

void StatusLabel::changeEvent(QEvent* event)
{
  if (event->type() == QEvent::PaletteChange)
    icon_lbl_->setPixmap(icon_.pixmap(icon_size_));
  QWidget::changeEvent(event);
}
