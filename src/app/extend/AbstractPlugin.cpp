#include "AbstractPlugin.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

AbstractPlugin::AbstractPlugin(QObject* parent) : QObject(parent) {}

AbstractPlugin::~AbstractPlugin() {}

void AbstractPlugin::init(Ui::MainWindow* ui) {
  initView(ui);
  doInit();
}

void AbstractPlugin::initView(Ui::MainWindow* ui) { Q_UNUSED(ui); }
