#ifndef TOOL_H
#define TOOL_H

#include <QStringList>

class Tool
{
public:
    static Tool* getInstance();

    void addTool(const QString& tool);

    QString activeTool() const;
    void changeActiveTool(const QString& activeTool);

private:
    QString     m_activeTool;
    QStringList m_tools;

private:
    Tool();
    ~Tool();
};

#endif // TOOL_H
