#include "ToolButtonGroup.h"

ToolButtonGroup::ToolButtonGroup(QObject* parent) : QObject(parent) {
}

ToolButtonGroup::~ToolButtonGroup() {
}

void ToolButtonGroup::add(QToolButton* toolButton) {
  m_toolButtons << toolButton;
  connect(toolButton, &QToolButton::clicked, this, &ToolButtonGroup::onExclusiveButtonPress);
}

void ToolButtonGroup::onExclusiveButtonPress() {
  QToolButton* clickedButton = dynamic_cast<QToolButton*>(sender());
  clickedButton->setDown(true);
  foreach (QToolButton* toolButton, m_toolButtons) {
    if (clickedButton != toolButton) {
      toolButton->setDown(false);
    }
  }
}

QList<QToolButton*> ToolButtonGroup::toolButtons() const {
  return m_toolButtons;
}

void ToolButtonGroup::activateDefault() {
  QToolButton* firstButton = m_toolButtons.first();
  if (firstButton) {
    firstButton->clicked();
  }
}
