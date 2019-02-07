#include "Tool.h"

Tool* Tool::getInstance() {
  static Tool s;
  return &s;
}

void Tool::addTool(const QString& tool) { m_tools << tool; }

void Tool::changeActiveTool(const QString& nodeToolName) { m_activeToolName = nodeToolName; }

QString Tool::activeTool() const { return m_activeToolName; }

Tool::Tool(QObject* parent) : QObject(parent) {}

Tool::~Tool() {}
