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

#include "application.h"

#include <QFileOpenEvent>

Application::Application(int& argc, char** argv) : QApplication(argc, argv)
{
}

bool Application::event(QEvent* e)
{
  if (e->type() == QEvent::FileOpen) {
    QFileOpenEvent *open_event = static_cast<QFileOpenEvent*>(e);
    QString file = !open_event->file().isEmpty() ? open_event->file() : open_event->url().toLocalFile();
    if (!file.isEmpty()) {
      emit fileOpened(open_event->file());
      open_event->accept();
    }
    return open_event->isAccepted();
  }
  return QApplication::event(e);
}
