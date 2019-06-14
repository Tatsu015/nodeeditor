#include "AbstractPlugin.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

AbstractPlugin::AbstractPlugin(QObject* parent) : QObject(parent) {
}

AbstractPlugin::~AbstractPlugin() {
}

void AbstractPlugin::init(MainWindow* mainWindow, Ui::MainWindow* ui) {
  initView(mainWindow, ui);
  doInit();
}

void AbstractPlugin::initView(MainWindow* mainWindow, Ui::MainWindow* ui) {
  Q_UNUSED(ui);
}

void AbstractPlugin::reset() {
}
