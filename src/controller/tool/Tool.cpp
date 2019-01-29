#include "Tool.h"

Tool* Tool::getInstance()
{
    static Tool s;
    return &s;
}

void Tool::addTool(const QString& tool)
{
    m_tools << tool;
}

void Tool::changeActiveTool(const QString& activeTool)
{
    m_activeTool = activeTool;
}

QString Tool::activeTool() const
{
    return m_activeTool;
}

Tool::Tool()
{
}

Tool::~Tool()
{
}
