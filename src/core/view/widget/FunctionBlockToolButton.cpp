#include "FunctionBlockToolButton.h"
#include "Define.h"
#include "Editor.h"
#include "NodeEditTool.h"
#include "Sheet.h"
#include <QDebug>
#include <QMenu>

const static QString DEFAULT_TEXT = "No FB exist";

FunctionBlockToolButton::FunctionBlockToolButton(QWidget* parent) : QToolButton(parent), m_menu(new QMenu()) {
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  setMenu(m_menu);
  setPopupMode(MenuButtonPopup);
  setEnabled(false);
  setText(DEFAULT_TEXT);
  setFixedWidth(100);
  setIcon(QIcon("../resource/fb.png"));
  setToolTip("Other sheet");
  connect(this, &FunctionBlockToolButton::clicked, this, &FunctionBlockToolButton::onChangeNodeType);
}

FunctionBlockToolButton::~FunctionBlockToolButton() {
}

void FunctionBlockToolButton::addSheet(Sheet* sheet) {
  QAction* action = new QAction(sheet->name());
  m_menu->addAction(action);
  setEnabled(true);
  // sheet count from 0 to 1, button text change from DEFAULT_TEXT to sheet name
  if (1 == m_menu->actions().count()) {
    setText(action->text());
  }
  connect(action, &QAction::triggered, this, &FunctionBlockToolButton::onChangeFunctionBlock);
}

void FunctionBlockToolButton::changeSheet(Sheet* sheet) {
  qDebug() << "chcanged!";
}

void FunctionBlockToolButton::removeSheet(Sheet* sheet) {
  foreach (QAction* action, m_menu->actions()) {
    if (action->text() == sheet->name()) {
      m_menu->removeAction(action);
      disconnect(action, &QAction::triggered, this, &FunctionBlockToolButton::onChangeFunctionBlock);
      if (0 >= m_menu->actions().count()) {
        setEnabled(false);
        setText(DEFAULT_TEXT);
      }
      return;
    }
  }
}

bool FunctionBlockToolButton::hasAction() const {
  return !m_menu->actions().isEmpty();
}

void FunctionBlockToolButton::onChangeFunctionBlock() {
  QAction* action = dynamic_cast<QAction*>(sender());
  setText(action->text());
}

void FunctionBlockToolButton::onChangeNodeType() {
  NodeEditTool* tool = dynamic_cast<NodeEditTool*>(Editor::getInstance()->tool(TOOL_NODE_EDIT));
  tool->setActiveNodeType(text());
}
