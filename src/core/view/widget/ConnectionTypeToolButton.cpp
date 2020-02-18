#include "ConnectionTypeToolButton.h"
#include "ConnectionCreateTool.h"
#include "ConnectionFactory.h"
#include "Define.h"
#include "Editor.h"
#include <QMenu>

ConnectionTypeToolButton::ConnectionTypeToolButton(QWidget* parent) : QToolButton(parent) {
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  setPopupMode(MenuButtonPopup);
  setFixedWidth(100);
  setToolTip("Connection");
}

ConnectionTypeToolButton::~ConnectionTypeToolButton() {
}

void ConnectionTypeToolButton::setup() {
  bool isFirst = true;
  foreach (QString connectionType, ConnectionFactory::getInstance()->connectionTypes()) {
    QAction* action = new QAction(connectionType);
    addAction(action);
    connect(action, &QAction::triggered, this, &ConnectionTypeToolButton::onChangeConnetionType);

    if (isFirst) {
      action->trigger();
      isFirst = false;
    }
  }
}

void ConnectionTypeToolButton::onChangeConnetionType() {
  QString currentConnectionType = dynamic_cast<QAction*>(sender())->text();
  setText(currentConnectionType);
  setIcon(ConnectionFactory::getInstance()->createIcon(currentConnectionType));
  ConnectionCreateTool* tool = dynamic_cast<ConnectionCreateTool*>(Editor::getInstance()->tool(TOOL_CONNECTION_CREATE));
  tool->setActiveConnectionType(currentConnectionType);
}
