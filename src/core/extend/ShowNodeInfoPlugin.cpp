#include "ShowNodeInfoPlugin.h"
#include "AbstractConnection.h"
#include "AbstractNode.h"
#include "Editor.h"
#include "MenuManager.h"
#include "Project.h"
#include "Sheet.h"
#include <QMenu>

ShowNodeInfoPlugin::ShowNodeInfoPlugin(QObject* parent) : AbstractPlugin(parent), m_menu(new QMenu("Node Infomation")) {
}

ShowNodeInfoPlugin::~ShowNodeInfoPlugin() {
}

void ShowNodeInfoPlugin::doInit() {

  m_showNodeNameAction = new QAction("Show Node Name");
  m_showNodeNameAction->setCheckable(true);
  m_showNodeNameAction->setChecked(true);
  m_menu->addAction(m_showNodeNameAction);
  connect(m_showNodeNameAction, &QAction::triggered, this, &ShowNodeInfoPlugin::onExecuteShowNodeName);

  m_showNodeIdAction = new QAction("Show Node Id");
  m_showNodeIdAction->setCheckable(true);
  m_showNodeIdAction->setChecked(true);
  m_menu->addAction(m_showNodeIdAction);
  connect(m_showNodeIdAction, &QAction::triggered, this, &ShowNodeInfoPlugin::onExecuteShowNodeId);

  QMenu* menu = MenuManager::getInstance()->menu(MenuManager::MENU_VIEW);
  menu->addMenu(m_menu);
}

void ShowNodeInfoPlugin::onExecuteShowNodeName() {
  Project* project = Editor::getInstance()->project();
  bool nextState = m_showNodeNameAction->isChecked();
  project->setNodeNameVisible(nextState);
  foreach (Sheet* sheet, project->sheets()) {
    foreach (AbstractNode* node, sheet->nodes()) { node->setNameTextVisible(nextState); }
  }
  m_showNodeNameAction->setChecked(nextState);
}

void ShowNodeInfoPlugin::onExecuteShowNodeId() {
  Project* project = Editor::getInstance()->project();
  bool nextState = m_showNodeIdAction->isChecked();
  project->setNodeIdVisible(nextState);
  foreach (Sheet* sheet, project->sheets()) {
    foreach (AbstractNode* node, sheet->nodes()) { node->setIdTextVisible(nextState); }
    foreach (AbstractConnection* connection, sheet->connections()) { connection->setIdTextVisible(nextState); }
  }
  m_showNodeIdAction->setChecked(nextState);
}
