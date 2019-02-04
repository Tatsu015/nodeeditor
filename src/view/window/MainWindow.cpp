#include <QAction>
#include <QToolButton>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Scene.h"
#include "Tool.h"
#include "AnalyzeCircuitAction.h"
#include <QDebug>
#include <QMenu>
#include "Editor.h"
#include "ErrorListWidget.h"
#include "NodeFactory.h"
#include "ConnectionFactory.h"
#include "Connection.h"
#include "AbstractNode.h"
#include "HiddenNode.h"
#include "InNode.h"
#include "OutNode.h"
#include "SaveAction.h"
#include "OpenAction.h"
#include "Define.h"

const static QString MODE_IN     = "In";
const static QString MODE_OUT    = "Out";
const static QString MODE_HIDDEN = "Hidden";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    Editor::getInstance()->setGraphicsView(m_ui->graphicsView);
    Editor::getInstance()->init();

    NodeFactory::getInstance()->addNode(NODE_IN,     new InNode());
    NodeFactory::getInstance()->addNode(NODE_OUT,    new OutNode());
    NodeFactory::getInstance()->addNode(NODE_HIDDEN, new HiddenNode());

    ConnectionFactory::getInstance()->addConnection(CONNECTION, new Connection());

    // setup graphics view
    m_ui->graphicsView->setBackgroundBrush(QBrush(QColor(75,75,75)));
    m_ui->graphicsView->setRenderHints(QPainter::Antialiasing);

    // setup tool bar
    addToolBar(Qt::LeftToolBarArea, m_ui->mainToolBar);
    addToolBarAction(new QAction(/*QIcon("../resource/in.png")    , */NODE_IN    ));
    addToolBarAction(new QAction(/*QIcon("../resource/out.png")   , */NODE_OUT   ));
    addToolBarAction(new QAction(/*QIcon("../resource/hidden.png"), */NODE_HIDDEN));
    setDefaultToolBarAction(NODE_HIDDEN);

    // setup action
    Editor::getInstance()->addAction(new OpenAction());
    Editor::getInstance()->addAction(new SaveAction());

    // setup menu
    QMenu* fileMenu = new QMenu("File");
    m_ui->menuBar->addMenu(fileMenu);
    fileMenu->addAction(Editor::getInstance()->action(SaveAction::ACTION_SAVE)->action());
    fileMenu->addAction(Editor::getInstance()->action(OpenAction::ACTION_OPEN)->action());

    AnalyzeCircuitAction* ep = new AnalyzeCircuitAction();
    m_ui->menuBar->addAction(ep->ExportScriptAction());

    addDockWidget(static_cast<Qt::DockWidgetArea>(8), ep->DockWidget());
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::addToolBarAction(QAction* action)
{
    m_ui->mainToolBar->addAction(action);

    ToolBarAction* toolBarAction = new ToolBarAction();
    toolBarAction->m_action = action;
    toolBarAction->m_button = dynamic_cast<QToolButton*>(m_ui->mainToolBar->widgetForAction(action));
    QString actionName = action->text();

    toolBarAction->m_button->setCheckable(true);

    m_toolBarActions[actionName] = toolBarAction;
    Tool::getInstance()->addTool(actionName);

    connect(toolBarAction->m_action, &QAction::triggered, [this, toolBarAction]{
        Tool::getInstance()->changeActiveTool(toolBarAction->m_action->text());
        foreach (ToolBarAction* toolBarAction, m_toolBarActions.values()) {
            toolBarAction->m_button->setChecked(false);
        }
        toolBarAction->m_button->setChecked(true);
    });
}

void MainWindow::setDefaultToolBarAction(QString actionName)
{
    Tool::getInstance()->changeActiveTool(actionName);
    QAction* acr = m_toolBarActions[actionName]->m_action;
    acr->setChecked(true);
}
