#include "MainWindow.h"
#include "Builder.h"
#include "Editor.h"
#include "Project.h"
#include "SheetChangeHistoryController.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
  m_ui->setupUi(this);
  Builder::getInstance()->build(this, m_ui);
  Editor::getInstance()->run();
}

MainWindow::~MainWindow() {
  delete m_ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
  if ((Qt::Key_Right == event->key()) && (Qt::AltModifier == event->modifiers())) {
    QString sheetName = SheetChangeHistoryController::getInstance()->next();
    if (!sheetName.isEmpty()) {
      Editor::getInstance()->project()->changeActiveSheet(sheetName);
    }
  } else if ((Qt::Key_Left == event->key()) && (Qt::AltModifier == event->modifiers())) {
    QString sheetName = SheetChangeHistoryController::getInstance()->previous();
    if (!sheetName.isEmpty()) {
      Editor::getInstance()->project()->changeActiveSheet(sheetName);
    }
  }
  QMainWindow::keyReleaseEvent(event);
}
