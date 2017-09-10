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

#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>

class ImageLabel : public QLabel
{
  Q_OBJECT
  Q_PROPERTY(QImage image READ image WRITE setImage)

public:
  explicit ImageLabel(QWidget *parent = nullptr);

  QImage image() const;

public slots:
  void setImage(const QImage& image);

protected:
  void paintEvent(QPaintEvent* event);
  void resizeEvent(QResizeEvent* event);

private:
  void updateImage();

private:
  QPixmap transp_txd_;
  QImage cur_image_;
};

#endif // IMAGELABEL_H
