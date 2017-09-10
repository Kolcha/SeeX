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

#include "imagelabel.h"

#include <QPainter>

ImageLabel::ImageLabel(QWidget *parent) : QLabel(parent), transp_txd_(16, 16)
{
  transp_txd_.fill(Qt::white);
  QPainter p(&transp_txd_);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      QRect r(j*8, i*8, 8, 8);
      p.fillRect(r, (i+j) % 2 == 0 ? QColor(200, 200, 200) : QColor(220, 220, 220));
    }
  }
  setAlignment(Qt::AlignCenter);
}

void ImageLabel::paintEvent(QPaintEvent* event)
{
  if (pixmap() && pixmap()->hasAlpha()) {
    QPainter p(this);
    QRect img_rect(rect().center() - pixmap()->rect().center(), pixmap()->size());
    p.fillRect(img_rect, transp_txd_);
  }
  QLabel::paintEvent(event);
}
