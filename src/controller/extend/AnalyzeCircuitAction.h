#ifndef ANALYZECURCUIT_H
#define ANALYZECURCUIT_H

#include <QObject>
#include <QList>
#include <QDockWidget>
#include "ErrorListWidget.h"
#include "Common.h"

class QAction;
class AbstractNode;

class AnalyzeCircuitAction : public QObject
{
    Q_OBJECT

public:
    AnalyzeCircuitAction(QObject *parent=nullptr);
    virtual ~AnalyzeCircuitAction();

    QAction* ExportScriptAction() const;

    bool CheckAllPortFilled(const QList<AbstractNode*>& nodes);

    QDockWidget* DockWidget() const;

signals:
    void OccurError(AbstractNode* node, const QString& errorMessage, BugType type);
    void ClearError();


private slots:
    void Export();

private:
    struct ConnectedGraph
    {
        QString m_name;
        uint64_t m_id;
        QString m_description;
        QList<AbstractNode*> m_outNodes;
    };

private:
    QList<ConnectedGraph*> ConnectedGraphs(const QList<AbstractNode*>& nodes);
    QList<AbstractNode*> ExecuteOrderSort(ConnectedGraph* fbd);

    QList<AbstractNode*> InNodes(const QList<AbstractNode*>& nodes);
    QList<AbstractNode*> OutNodes(const QList<AbstractNode*>& nodes);
    QList<AbstractNode*> HiddenNodes(const QList<AbstractNode*>& nodes);

private:
    QAction* m_exportScriptAction = nullptr;
    QDockWidget* m_dockWidget = nullptr;
    ErrorListWidget* m_listWidget = nullptr;
};

#endif // ANALYZECURCUIT_H
