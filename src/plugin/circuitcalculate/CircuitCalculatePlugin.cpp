#include "CircuitCalculatePlugin.h"
#include <QApplication>
#include <QDockWidget>
#include <QMenu>
#include "Editor.h"
#include "IOTableWidget.h"
#include "MainWindow.h"
#include "MenuManager.h"
#include "Project.h"
#include "Scene.h"
#include "ui_MainWindow.h"

CircuitCalculatePlugin::CircuitCalculatePlugin() : AbstractPlugin() {}

CircuitCalculatePlugin::~CircuitCalculatePlugin() {}

void CircuitCalculatePlugin::initView(MainWindow* mainWindow, Ui::MainWindow* ui) {
  QDockWidget* ioSetDockWidget = new QDockWidget();
  IOTableWidget* ioTableWidget = new IOTableWidget();
  ioSetDockWidget->setWidget(ioTableWidget);
  Editor::getInstance()->project()->scene()->addSceneObserver(ioTableWidget);
  mainWindow->addDockWidget(Qt::RightDockWidgetArea, ioSetDockWidget);
}

void CircuitCalculatePlugin::doInit() {
  QMenu* debugMenu = new QMenu("Debug");

  QAction* circuitCalculateAction = new QAction("CircuitCalculate");
  debugMenu->addAction(circuitCalculateAction);

  MenuManager::getInstance()->addMenu(debugMenu);
  connect(circuitCalculateAction, &QAction::triggered, this, &CircuitCalculatePlugin::onExecute);
}

void CircuitCalculatePlugin::onExecute() {}
