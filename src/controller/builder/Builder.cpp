#include "Builder.h"

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

Builder* Builder::getInstance()
{
    static Builder s;
    return &s;
}

void Builder::build(MainWindow *mainWindow, Ui::MainWindow *ui)
{
    buildGraphicsView(mainWindow, ui);
    buildMenu(mainWindow,         ui);
    buildToolBar(mainWindow,      ui);
    buildDockWidget(mainWindow,   ui);
}

void Builder::buildGraphicsView(MainWindow *mainWindow, Ui::MainWindow *ui)
{
    Q_UNUSED(mainWindow);

    ui->graphicsView->setBackgroundBrush(QBrush(QColor(75,75,75)));
    ui->graphicsView->setRenderHints(QPainter::Antialiasing);
}

void Builder::buildMenu(MainWindow *mainWindow, Ui::MainWindow *ui)
{
    Q_UNUSED(mainWindow);

    // setup menu
    QMenu* fileMenu = new QMenu("File");
    ui->menuBar->addMenu(fileMenu);
    fileMenu->addAction(Editor::getInstance()->action(SaveAction::ACTION_SAVE)->action());
    fileMenu->addAction(Editor::getInstance()->action(OpenAction::ACTION_OPEN)->action());
}

void Builder::buildToolBar(MainWindow *mainWindow, Ui::MainWindow *ui)
{
    // setup tool bar
    mainWindow->addToolBar(Qt::LeftToolBarArea, ui->mainToolBar);
    addToolBarAction(new QAction(/*QIcon("../resource/in.png")    , */NODE_IN    ), ui);
    addToolBarAction(new QAction(/*QIcon("../resource/out.png")   , */NODE_OUT   ), ui);
    addToolBarAction(new QAction(/*QIcon("../resource/hidden.png"), */NODE_HIDDEN), ui);
    setDefaultToolBarAction(NODE_HIDDEN);
}

void Builder::buildDockWidget(MainWindow *mainWindow, Ui::MainWindow *ui)
{
    AnalyzeCircuitAction* ep = new AnalyzeCircuitAction();
    ui->menuBar->addAction(ep->ExportScriptAction());

    mainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), ep->DockWidget());
}

void Builder::addToolBarAction(QAction *action, Ui::MainWindow *ui)
{
    ui->mainToolBar->addAction(action);

    ToolBarAction* toolBarAction = new ToolBarAction();
    toolBarAction->m_action = action;
    toolBarAction->m_button = dynamic_cast<QToolButton*>(ui->mainToolBar->widgetForAction(action));
    QString actionName = action->text();

    toolBarAction->m_button->setCheckable(true);

    m_toolBarActions[actionName] = toolBarAction;
    Tool::getInstance()->addTool(actionName);

    connect(toolBarAction->m_action, &QAction::triggered, this, &Builder::onChangeTool);
}

void Builder::setDefaultToolBarAction(QString actionName)
{
    Tool::getInstance()->changeActiveTool(actionName);
    QAction* acr = m_toolBarActions[actionName]->m_action;
    acr->setChecked(true);
}

void Builder::onChangeTool()
{
    QString toolName = dynamic_cast<QAction*>(sender())->text();
    Tool::getInstance()->changeActiveTool(toolName);
}

Builder::Builder(QObject *parent):
    QObject(parent)
{
}

Builder::~Builder()
{
}

