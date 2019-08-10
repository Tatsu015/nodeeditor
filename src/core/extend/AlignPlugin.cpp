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

void AlignPlugin::doInit() {
  QMenu* editMenu = MenuManager::getInstance()->menu(MenuManager::MENU_EDIT);
  QMenu* alignMenu = new QMenu("Align");
  editMenu->addMenu(alignMenu);

  QAction* alignLeftAction = new QAction("Align Left");
  alignMenu->addAction(alignLeftAction);

  connect(alignLeftAction, &QAction::triggered, this, &AlignPlugin::onExecuteAlignLeft);

  QAction* alignRightAction = new QAction("Align Right");
  alignMenu->addAction(alignRightAction);

  connect(alignRightAction, &QAction::triggered, this, &AlignPlugin::onExecuteAlignRight);

  QAction* alignTopAction = new QAction("Align Top");
  alignMenu->addAction(alignTopAction);

  connect(alignTopAction, &QAction::triggered, this, &AlignPlugin::onExecuteAlignTop);

  QAction* alignBottomAction = new QAction("Align Bottom");
  alignMenu->addAction(alignBottomAction);

  connect(alignBottomAction, &QAction::triggered, this, &AlignPlugin::onExecuteAlignBottom);
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
  }
  scene->redraw();
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
  }
  scene->redraw();
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
  }
  scene->redraw();
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
  }
  scene->redraw();
}
