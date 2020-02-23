#include "AlignPlugin.h"
#include "AbstractNode.h"
#include "Editor.h"
#include "MenuManager.h"
#include "Project.h"
#include "Scene.h"
#include <QMenu>

AlignPlugin::AlignPlugin(QObject* parent) : AbstractPlugin(parent) {
}

AlignPlugin::~AlignPlugin() {
}

QMenu* AlignPlugin::contextSubMenu(QGraphicsSceneContextMenuEvent* event) const {
  Q_UNUSED(event);
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  QList<AbstractNode*> selectedNodes = scene->selectedNodes();
  if (1 >= selectedNodes.count()) {
    return nullptr;
  }
  return m_alignMenu;
}

void AlignPlugin::doInit() {
  useContextMenu(true);

  QMenu* editMenu = MenuManager::getInstance()->menu(MenuManager::MENU_EDIT);
  m_alignMenu = new QMenu("Align");
  editMenu->addMenu(m_alignMenu);

  m_alignLeftAction = new QAction("Align Left");
  m_alignMenu->addAction(m_alignLeftAction);

  connect(m_alignLeftAction, &QAction::triggered, this, &AlignPlugin::onExecuteAlignLeft);

  m_alignRightAction = new QAction("Align Right");
  m_alignMenu->addAction(m_alignRightAction);

  connect(m_alignRightAction, &QAction::triggered, this, &AlignPlugin::onExecuteAlignRight);

  m_alignTopAction = new QAction("Align Top");
  m_alignMenu->addAction(m_alignTopAction);

  connect(m_alignTopAction, &QAction::triggered, this, &AlignPlugin::onExecuteAlignTop);

  m_alignBottomAction = new QAction("Align Bottom");
  m_alignMenu->addAction(m_alignBottomAction);

  connect(m_alignBottomAction, &QAction::triggered, this, &AlignPlugin::onExecuteAlignBottom);
}

void AlignPlugin::onExecuteAlignLeft() {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  QList<AbstractNode*> selectedNodes = scene->selectedNodes();
  if (1 >= selectedNodes.count()) {
    return;
  }

  qreal minX = selectedNodes.at(0)->x();
  foreach (AbstractNode* node, selectedNodes) {
    if (minX > node->x()) {
      minX = node->x();
    }
  }
  foreach (AbstractNode* node, selectedNodes) {
    qreal y = node->y();
    node->setPos(minX, y);
    node->redraw();
  }
}

void AlignPlugin::onExecuteAlignRight() {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  QList<AbstractNode*> selectedNodes = scene->selectedNodes();
  if (1 >= selectedNodes.count()) {
    return;
  }

  qreal maxX = selectedNodes.at(0)->x();
  foreach (AbstractNode* node, selectedNodes) {
    if (maxX < node->x()) {
      maxX = node->x();
    }
  }
  foreach (AbstractNode* node, selectedNodes) {
    qreal y = node->y();
    node->setPos(maxX, y);
    node->redraw();
  }
}

void AlignPlugin::onExecuteAlignTop() {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  QList<AbstractNode*> selectedNodes = scene->selectedNodes();
  if (1 >= selectedNodes.count()) {
    return;
  }

  qreal maxY = selectedNodes.at(0)->y();
  foreach (AbstractNode* node, selectedNodes) {
    if (maxY > node->y()) {
      maxY = node->y();
    }
  }
  foreach (AbstractNode* node, selectedNodes) {
    qreal x = node->x();
    node->setPos(x, maxY);
    node->redraw();
  }
}

void AlignPlugin::onExecuteAlignBottom() {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  QList<AbstractNode*> selectedNodes = scene->selectedNodes();
  if (1 >= selectedNodes.count()) {
    return;
  }

  qreal minY = selectedNodes.at(0)->y();
  foreach (AbstractNode* node, selectedNodes) {
    if (minY < node->y()) {
      minY = node->y();
    }
  }
  foreach (AbstractNode* node, selectedNodes) {
    qreal x = node->x();
    node->setPos(x, minY);
    node->redraw();
  }
}
