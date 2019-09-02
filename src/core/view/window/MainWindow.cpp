#include "MainWindow.h"
#include "Builder.h"
#include "Editor.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
  m_ui->setupUi(this);
  Builder::getInstance()->build(this, m_ui);
  Editor::getInstance()->run();
}

MainWindow::~MainWindow() {
  delete m_ui;
}
