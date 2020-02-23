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
  Q_UNUSED(mainWindow);
  Q_UNUSED(ui);
}

void AbstractPlugin::useContextMenu(const bool isUse) {
  m_isContextMenuUse = isUse;
}

bool AbstractPlugin::isContextMenuUse() const {
  return m_isContextMenuUse;
}

QMenu* AbstractPlugin::contextSubMenu(QGraphicsSceneContextMenuEvent* event) const {
  Q_UNUSED(event);
  return nullptr;
}

void AbstractPlugin::reset() {
}

QList<QAction*> AbstractPlugin::contextMenuActions(QGraphicsSceneContextMenuEvent* event) const {
  Q_UNUSED(event);
  return QList<QAction*>();
}
