#include "ReplaceNodePlugin.h"
#include "AbstractNode.h"
#include "Connection.h"
#include "Editor.h"
#include "NodeFactory.h"
#include "NodeReplaceCommand.h"
#include "Port.h"
#include "Project.h"
#include "Scene.h"
#include "Sheet.h"
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>
#include <QInputDialog>

ReplaceNodePlugin::ReplaceNodePlugin(QObject* parent) : AbstractPlugin(parent) {
}

ReplaceNodePlugin::~ReplaceNodePlugin() {
}

QList<QAction*> ReplaceNodePlugin::contextMenuActions(QGraphicsSceneContextMenuEvent* event) const {
  m_nameCache.clear();
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  m_replaceNodeCache = scene->findNode(event->scenePos());
  if (!m_replaceNodeCache) {
    return QList<QAction*>();
  }

  foreach (AbstractNode* nodeBase, NodeFactory::getInstance()->nodes()) {
    if (m_replaceNodeCache->nodeType() == nodeBase->nodeType()) {
      continue;
    }
    if (m_replaceNodeCache->isReplaceable(nodeBase)) {
      m_nameCache << nodeBase->nodeType();
      return QList<QAction*>({m_action});
    }
  }

  return QList<QAction*>();
}

void ReplaceNodePlugin::doInit() {
  useContextMenu(true);

  m_action = new QAction("Replace");
  connect(m_action, &QAction::triggered, this, &ReplaceNodePlugin::onExecute);
}

void ReplaceNodePlugin::onExecute() {
  Scene* scene = Editor::getInstance()->project()->scene();
  QList<AbstractNode*> nodes = scene->selectedNodes();
  if (0 >= nodes.count()) {
    return;
  }

  QInputDialog dialog;
  bool ok;
  QString replaceToNodeType = dialog.getItem(nullptr, "Replace Node", "Replace to", m_nameCache, 0, false, &ok);
  if (!ok) {
    return;
  }
  if (replaceToNodeType.isEmpty()) {
    return;
  }

  Sheet* activeSheet = Editor::getInstance()->project()->activeSheet();
  AbstractNode* node = NodeFactory::getInstance()->createNode(activeSheet, replaceToNodeType);
  int32_t inputPortCountDiff = m_replaceNodeCache->inputPortCount() - node->inputPortCount();
  if (0 < inputPortCountDiff) {
    for (int32_t i = 0; i < inputPortCountDiff; ++i) {
      node->addInputPort(new Port(Input, node->portCount() + 1, node));
    }
  }
  int32_t outputPortCountDiff = m_replaceNodeCache->outputPortCount() - node->outputPortCount();
  if (0 < outputPortCountDiff) {
    for (int32_t i = 0; i < outputPortCountDiff; ++i) {
      node->addOutputPort(new Port(Output, node->portCount() + 1, node));
    }
  }

  Editor::getInstance()->addCommand(new NodeReplaceCommand(scene, activeSheet, m_replaceNodeCache, node));
}
