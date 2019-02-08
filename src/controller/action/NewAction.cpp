#include "NewAction.h"
#include <QAction>
#include <QDebug>
#include <QFile>
#include "Define.h"
#include "Editor.h"
#include "Project.h"

NewAction::NewAction(QObject *parent) : AbstractAction(parent) {
  m_action = new QAction(ACTION_NEW);
  connect(m_action, &QAction::triggered, this, &NewAction::execute);
}

NewAction::~NewAction() {}

QString NewAction::name() { return ACTION_NEW; }

void NewAction::execute() {
  Editor::getInstance()->reset();
  //    QFile file("test.json");
  //    if(!file.New(QIODevice::ReadOnly)){
  //        return;
  //    }
}
