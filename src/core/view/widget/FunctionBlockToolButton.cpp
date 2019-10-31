#include "FunctionBlockToolButton.h"
#include "Sheet.h"
#include <QDebug>
#include <QMenu>

FunctionBlockToolButton::FunctionBlockToolButton(QWidget* parent) : QToolButton(parent), m_menu(new QMenu()) {
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  setMenu(m_menu);
  setPopupMode(MenuButtonPopup);
  setEnabled(false);
  setText("No FB exist");
  setFixedWidth(100);
  setIcon(QIcon("../resource/fb.png"));
}

FunctionBlockToolButton::~FunctionBlockToolButton() {
}

void FunctionBlockToolButton::addSheet(Sheet* sheet) {
  QAction* action = new QAction(sheet->name());
  m_menu->addAction(action);
  setEnabled(true);
  connect(action, &QAction::triggered, this, &FunctionBlockToolButton::onChangeFunctionBlock);
}

void FunctionBlockToolButton::changeSheet(Sheet* sheet) {
  qDebug() << "chcanged!";
}

void FunctionBlockToolButton::removeSheet(Sheet* sheet) {
  foreach (QAction* action, m_menu->actions()) {
    if (action->text() == sheet->name()) {
      m_menu->removeAction(action);
      if (0 >= m_menu->actions().count()) {
        setEnabled(false);
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
