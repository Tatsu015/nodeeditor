#ifndef NODETOOLBAR_H
#define NODETOOLBAR_H

#include <QToolBar>

class NodeCreateTool;

class NodeToolBar : public QToolBar
{
    Q_OBJECT

public:
    NodeToolBar(QWidget *parent = nullptr);
    virtual ~NodeToolBar();

    void addToolBarAction(const QString &nodeType);

    void setNodeCreationTool(NodeCreateTool *nodeCreationTool);

private slots:
    void onChangeTool();

private:
    NodeCreateTool* m_nodeCreationTool = nullptr;
};

#endif // NODETOOLBAR_H
