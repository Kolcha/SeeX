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

#include "statuslabel.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QIcon>

StatusLabel::StatusLabel(QWidget *parent) : QWidget(parent)
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
