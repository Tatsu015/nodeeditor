#include "MainWindow.h"
#include "Builder.h"
#include "Editor.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
  m_ui->setupUi(this);

  Editor::getInstance()->setGraphicsView(m_ui->graphicsView);
  Editor::getInstance()->init();

  Builder::getInstance()->build(this, m_ui);
}

MainWindow::~MainWindow() { delete m_ui; }
