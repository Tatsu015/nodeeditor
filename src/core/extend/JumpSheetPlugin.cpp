#include "JumpSheetPlugin.h"
#include "AbstractNode.h"
#include "Editor.h"
#include "FunctionBlockNode.h"
#include "MenuManager.h"
#include "Project.h"
#include "Scene.h"
#include "Sheet.h"
#include "SheetChangeHistoryController.h"
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

JumpSheetPlugin::JumpSheetPlugin(QObject* parent) : AbstractPlugin(parent) {
}

JumpSheetPlugin::~JumpSheetPlugin() {
}

QList<QAction*> JumpSheetPlugin::contextMenuActions(QGraphicsSceneContextMenuEvent* event) const {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  QList<AbstractNode*> nodes = scene->findNodes(event->scenePos());
  if (1 != nodes.count()) {
    return QList<QAction*>();
  }
  m_targetFunctionBlockNode = dynamic_cast<FunctionBlockNode*>(nodes.first());
  if (m_targetFunctionBlockNode) {
    return QList<QAction*>({m_action});
  }
  return QList<QAction*>();
}

void JumpSheetPlugin::doInit() {
  useContextMenu(true);

  m_action = new QAction("Jump To Definition");
  connect(m_action, &QAction::triggered, this, &JumpSheetPlugin::onExecute);
}

void JumpSheetPlugin::onExecute() {
  Project* project = Editor::getInstance()->project();
  QString sheetName = m_targetFunctionBlockNode->nodeType();
  project->changeActiveSheet(sheetName);
  SheetChangeHistoryController::getInstance()->add(sheetName);
}
