#include "AnalyzeCircuit.h"
#include "InNode.h"
#include "OutNode.h"
#include "HiddenNode.h"
#include "Scene.h"
#include "Port.h"
#include "ErrorListWidget.h"
#include <QAction>
#include <QDebug>
#include <algorithm>

AnalyzeCircuit::AnalyzeCircuit(Scene* scene, QObject *parent):
    QObject(parent),
    m_scene(scene)
{
    m_exportScriptAction = new QAction("Export");
    m_exportScriptAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));

    m_dockWidget = new QDockWidget();
    m_listWidget = new ErrorListWidget();
    m_dockWidget->setWidget(m_listWidget);

    QObject::connect(m_exportScriptAction, &QAction::triggered,
                     this, &AnalyzeCircuit::Export);
}

AnalyzeCircuit::~AnalyzeCircuit()
{
}

void AnalyzeCircuit::Export()
{
    QList<Node*> nodes = m_scene->nodes();

    if(!CheckAllPortFilled(nodes)){
        qDebug() << "Do not connect finish!";
        return;
    }
    QList<ConnectedGraph*> connectedGtaphs = ConnectedGraphs(m_scene->nodes());
    foreach (ConnectedGraph* fbd, connectedGtaphs) {
        ExecuteOrderSort(fbd);
    }
}

QList<AnalyzeCircuit::ConnectedGraph*> AnalyzeCircuit::ConnectedGraphs(const QList<Node*>& nodes)
{
    QList<ConnectedGraph*> fbds;
    QList<Node*> unusedNode = nodes;
    uint64_t id = 0;

    while (unusedNode.count()) {
        QList<Node*> connectedNodes;
        Node* node = unusedNode.last();
        QList<Node*> unvisitedNodes;
        unvisitedNodes << node;

        while (unvisitedNodes.count()) {
            Node* checkNode = unvisitedNodes.takeLast();
            connectedNodes << checkNode;
            unusedNode.removeOne(checkNode);
            foreach (Node* adjastNode, checkNode->adjastNodes()) {
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

QList<Node*> AnalyzeCircuit::ExecuteOrderSort(AnalyzeCircuit::ConnectedGraph* fbd)
{
    QList<Node*> visitedNodes;
    QList<Node*> unvisitedNodes = fbd->m_outNodes;

    while (unvisitedNodes.count()) {
        Node* visitNode = unvisitedNodes.takeLast();
        visitedNodes << visitNode;
        foreach (Node* adjastInNode, visitNode->adjastInNodes()) {
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
    foreach (Node* node, visitedNodes) {
        qDebug() << node->name();
    }
    return visitedNodes;
}

QList<Node*> AnalyzeCircuit::InNodes(const QList<Node*>& nodes)
{
    QList<Node*> inNodes;
    foreach (Node* node, nodes) {
        InNode* inNode = dynamic_cast<InNode*>(node);
        if(inNode){
            inNodes << inNode;
        }
    }
    return inNodes;
}

QList<Node*> AnalyzeCircuit::OutNodes(const QList<Node*>& nodes)
{
    QList<Node*> outNodes;
    foreach (Node* node, nodes) {
        OutNode* outNode = dynamic_cast<OutNode*>(node);
        if(outNode){
            outNodes << outNode;
        }
    }
    return outNodes;
}

QList<Node*> AnalyzeCircuit::HiddenNodes(const QList<Node*>& nodes)
{
    QList<Node*> hiddenNodes;
    foreach (Node* node, nodes) {
        HiddenNode* hiddenNode = dynamic_cast<HiddenNode*>(node);
        if(hiddenNode){
            hiddenNodes << hiddenNode;
        }
    }
    return hiddenNodes;
}

QDockWidget* AnalyzeCircuit::DockWidget() const
{
    return m_dockWidget;
}

QAction* AnalyzeCircuit::ExportScriptAction() const
{
    return m_exportScriptAction;
}

bool AnalyzeCircuit::CheckAllPortFilled(const QList<Node*>& nodes)
{
    ClearError();
    const QString BASE_MESSAGE = "not connected port : ";

    bool ret = true;
    foreach (Node* node, nodes) {
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
