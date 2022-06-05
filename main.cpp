#include "mainwindow.h"
#include "application.h"

int main(int argc, char* argv[])
{
  QApplication::setApplicationDisplayName("SeeX");
  QApplication::setApplicationName("SeeX");
  QApplication::setApplicationVersion("1.1.0");
  QApplication::setOrganizationName("Nick Korotysh");
  QApplication::setOrganizationDomain("seex.kolcha.github.io");
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
  Application a(argc, argv);
  MainWindow w;
  QObject::connect(&a, &Application::fileOpened, &w, &MainWindow::openFile);
  w.showMaximized();

  return a.exec();
}
