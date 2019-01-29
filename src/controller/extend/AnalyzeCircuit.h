#ifndef ANALYZECURCUIT_H
#define ANALYZECURCUIT_H

#include <QObject>
#include <QList>
#include <QDockWidget>
#include "ErrorListWidget.h"
#include "Common.h"

class QAction;
class Node;
class Scene;

class AnalyzeCircuit : public QObject
{
    Q_OBJECT

public:
    AnalyzeCircuit(Scene* scene, QObject *parent=nullptr);
    virtual ~AnalyzeCircuit();

    QAction* ExportScriptAction() const;

    bool CheckAllPortFilled(const QList<Node*>& nodes);

    QDockWidget* DockWidget() const;

signals:
    void OccurError(Node* node, const QString& errorMessage, BugType type);
    void ClearError();


private slots:
    void Export();

private:
    struct ConnectedGraph
    {
        QString m_name;
        uint64_t m_id;
        QString m_description;
        QList<Node*> m_outNodes;
    };

private:
    QList<ConnectedGraph*> ConnectedGraphs(const QList<Node*>& nodes);
    QList<Node*> ExecuteOrderSort(ConnectedGraph* fbd);

    QList<Node*> InNodes(const QList<Node*>& nodes);
    QList<Node*> OutNodes(const QList<Node*>& nodes);
    QList<Node*> HiddenNodes(const QList<Node*>& nodes);

private:
    QAction* m_exportScriptAction = nullptr;
    Scene*   m_scene = nullptr;
    QDockWidget* m_dockWidget = nullptr;
    ErrorListWidget* m_listWidget = nullptr;
};

#endif // ANALYZECURCUIT_H
