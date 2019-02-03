#include "AnalyzeCircuitAction.h"
#include "InNode.h"
#include "OutNode.h"
#include "HiddenNode.h"
#include "Port.h"
#include "ErrorListWidget.h"
#include "Editor.h"
#include "Project.h"
#include "Scene.h"
#include <QAction>
#include <QDebug>
#include <algorithm>

AnalyzeCircuitAction::AnalyzeCircuitAction(QObject *parent):
    QObject(parent)
{
    m_exportScriptAction = new QAction("Export");
    m_exportScriptAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));

    m_dockWidget = new QDockWidget();
    m_listWidget = new ErrorListWidget();
    m_dockWidget->setWidget(m_listWidget);

    QObject::connect(m_exportScriptAction, &QAction::triggered,
                     this, &AnalyzeCircuitAction::Export);
}

AnalyzeCircuitAction::~AnalyzeCircuitAction()
{
}

void AnalyzeCircuitAction::Export()
{

    QList<AbstractNode*> nodes = Editor::getInstance()->project()->scene()->nodes();

    if(!CheckAllPortFilled(nodes)){
        qDebug() << "Do not connect finish!";
        return;
    }
    QList<ConnectedGraph*> connectedGtaphs = ConnectedGraphs(nodes);
    foreach (ConnectedGraph* fbd, connectedGtaphs) {
        ExecuteOrderSort(fbd);
    }
}

QList<AnalyzeCircuitAction::ConnectedGraph*> AnalyzeCircuitAction::ConnectedGraphs(const QList<AbstractNode*>& nodes)
{
    QList<ConnectedGraph*> fbds;
    QList<AbstractNode*> unusedNode = nodes;
    uint64_t id = 0;

    while (unusedNode.count()) {
        QList<AbstractNode*> connectedNodes;
        AbstractNode* node = unusedNode.last();
        QList<AbstractNode*> unvisitedNodes;
        unvisitedNodes << node;

        while (unvisitedNodes.count()) {
            AbstractNode* checkNode = unvisitedNodes.takeLast();
            connectedNodes << checkNode;
            unusedNode.removeOne(checkNode);
            foreach (AbstractNode* adjastNode, checkNode->adjastNodes()) {
                if(!connectedNodes.contains(adjastNode)){
                    unvisitedNodes << adjastNode;
                }
            }
        }
        ConnectedGraph* fbd = new ConnectedGraph();
        fbd->m_outNodes = OutNodes(connectedNodes);
        fbd->m_id = ++id;
        fbd->m_name = "f" + QString::number(id);
        fbds << fbd;
    }

    return fbds;
}

QList<AbstractNode*> AnalyzeCircuitAction::ExecuteOrderSort(AnalyzeCircuitAction::ConnectedGraph* fbd)
{
    QList<AbstractNode*> visitedNodes;
    QList<AbstractNode*> unvisitedNodes = fbd->m_outNodes;

    while (unvisitedNodes.count()) {
        AbstractNode* visitNode = unvisitedNodes.takeLast();
        visitedNodes << visitNode;
        foreach (AbstractNode* adjastInNode, visitNode->adjastInNodes()) {
            if(!visitedNodes.contains(adjastInNode)){
                unvisitedNodes.append(adjastInNode);
            }
            else{
                visitedNodes.move(visitedNodes.indexOf(visitNode), visitedNodes.indexOf(adjastInNode));
            }
        }
    }

    std::reverse(visitedNodes.begin(), visitedNodes.end());
    qDebug() << "======  " + fbd->m_name + " ======";
    foreach (AbstractNode* node, visitedNodes) {
        qDebug() << node->name();
    }
    return visitedNodes;
}

QList<AbstractNode*> AnalyzeCircuitAction::InNodes(const QList<AbstractNode*>& nodes)
{
    QList<AbstractNode*> inNodes;
    foreach (AbstractNode* node, nodes) {
        InNode* inNode = dynamic_cast<InNode*>(node);
        if(inNode){
            inNodes << inNode;
        }
    }
    return inNodes;
}

QList<AbstractNode*> AnalyzeCircuitAction::OutNodes(const QList<AbstractNode*>& nodes)
{
    QList<AbstractNode*> outNodes;
    foreach (AbstractNode* node, nodes) {
        OutNode* outNode = dynamic_cast<OutNode*>(node);
        if(outNode){
            outNodes << outNode;
        }
    }
    return outNodes;
}

QList<AbstractNode*> AnalyzeCircuitAction::HiddenNodes(const QList<AbstractNode*>& nodes)
{
    QList<AbstractNode*> hiddenNodes;
    foreach (AbstractNode* node, nodes) {
        HiddenNode* hiddenNode = dynamic_cast<HiddenNode*>(node);
        if(hiddenNode){
            hiddenNodes << hiddenNode;
        }
    }
    return hiddenNodes;
}

QDockWidget* AnalyzeCircuitAction::DockWidget() const
{
    return m_dockWidget;
}

QAction* AnalyzeCircuitAction::ExportScriptAction() const
{
    return m_exportScriptAction;
}

bool AnalyzeCircuitAction::CheckAllPortFilled(const QList<AbstractNode*>& nodes)
{
    ClearError();
    const QString BASE_MESSAGE = "not connected port : ";

    bool ret = true;
    foreach (AbstractNode* node, nodes) {
        foreach (Port* port, node->ports()) {
            if(0 == port->connections().count()){
                QString msg = BASE_MESSAGE + node->name();
                m_listWidget->onAddErrorWidgetItem(node, msg, Error);
                ret = false;
            }
        }
    }
    return ret;
}
