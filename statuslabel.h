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
