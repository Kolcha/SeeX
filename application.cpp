#include "application.h"

#include <QFileOpenEvent>

bool Application::event(QEvent* e)
{
  if (e->type() == QEvent::FileOpen) {
    QFileOpenEvent* open_event = static_cast<QFileOpenEvent*>(e);
    QString file = !open_event->file().isEmpty() ? open_event->file() : open_event->url().toLocalFile();
    if (!file.isEmpty()) {
      emit fileOpened(open_event->file());
      open_event->accept();
    }
    return open_event->isAccepted();
  }
  return QApplication::event(e);
}
