#include "SaveAction.h"
#include <QAction>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "AbstractNode.h"
#include "Define.h"
#include "Editor.h"
#include "Project.h"

SaveAction::SaveAction(QObject *parent) : AbstractAction(parent) {
  m_action = new QAction(ACTION_SAVE);
  connect(m_action, &QAction::triggered, this, &SaveAction::execute);
}

SaveAction::~SaveAction() {}

QString SaveAction::name() { return ACTION_SAVE; }

void SaveAction::execute() { Editor::getInstance()->project()->save("test.json"); }
