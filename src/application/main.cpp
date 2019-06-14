#include "Editor.h"
#include "MainWindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  Editor::getInstance()->init();

  MainWindow w;
  w.show();

  return a.exec();
}
