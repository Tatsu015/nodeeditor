#ifndef TOOL_H
#define TOOL_H

#include <QObject>
#include <QStringList>

class Tool : public QObject
{
    Q_OBJECT

public:
    static Tool* getInstance();

    void addTool(const QString& tool);

    QString activeTool() const;

public slots:
    void changeActiveTool(const QString& nodeToolName);

private:
    QString     m_activeToolName;
    QStringList m_tools;

private:
    Tool(QObject *parent=nullptr);
    ~Tool();
};

#endif // TOOL_H
