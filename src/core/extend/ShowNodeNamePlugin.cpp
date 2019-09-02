#include "ShowNodeNamePlugin.h"
#include "AbstractNode.h"
#include "Editor.h"
#include "MenuManager.h"
#include "Project.h"
#include "Sheet.h"
#include <QMenu>

ShowNameViewPlugin::ShowNameViewPlugin(QObject* parent) : AbstractPlugin(parent) {
}

ShowNameViewPlugin::~ShowNameViewPlugin() {
}

void ShowNameViewPlugin::doInit() {
  QMenu* menu = MenuManager::getInstance()->menu(MenuManager::MENU_VIEW);

  m_action = new QAction("Show Node Name");
  m_action->setCheckable(true);
  m_action->setChecked(true);
  menu->addAction(m_action);

  connect(m_action, &QAction::triggered, this, &ShowNameViewPlugin::onExecute);
}

void ShowNameViewPlugin::onExecute() {
  Project* project = Editor::getInstance()->project();
  bool nextState = m_action->isChecked();
  project->setNodeNameVisible(nextState);
  foreach (Sheet* sheet, project->sheets()) {
    foreach (AbstractNode* node, sheet->nodes()) { node->setNameTextVisible(nextState); }
  }
  m_action->setChecked(nextState);
}
