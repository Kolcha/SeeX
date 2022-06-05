#include "statuslabel.h"

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

StatusLabel::StatusLabel(const QPixmap& pxm, const QString& txt, QWidget* parent) : StatusLabel(parent)
{
  setIcon(pxm);
  setText(txt);
}

StatusLabel::StatusLabel(const QString& pxm, const QString& txt, QWidget* parent) : StatusLabel(parent)
{
  setIcon(pxm);
  setText(txt);
}

QPixmap StatusLabel::icon() const
{
  return icon_lbl_->pixmap(Qt::ReturnByValue);
}

QString StatusLabel::text() const
{
  return text_lbl_->text();
}

void StatusLabel::setIcon(const QPixmap& icn)
{
  icon_lbl_->setPixmap(icn);
}

void StatusLabel::setIcon(const QString& icn)
{
  setIcon(QIcon(icn).pixmap(16));
}

void StatusLabel::setText(const QString& txt)
{
  text_lbl_->setText(txt);
}
