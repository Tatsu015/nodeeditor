#include <QAction>
#include <QToolButton>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Scene.h"
#include "Tool.h"
#include "AnalyzeCircuit.h"
#include <QDebug>
#include <QMenu>
#include "Editor.h"
#include "ErrorListWidget.h"
#include "Node.h"
#include "Save.h"
#include "Open.h"

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

    // setup graphics view
    m_ui->graphicsView->setBackgroundBrush(QBrush(QColor(75,75,75)));
    m_ui->graphicsView->setRenderHints(QPainter::Antialiasing);

    // setup tool bar
    addToolBar(Qt::LeftToolBarArea, m_ui->mainToolBar);
    addToolBarAction(new QAction(/*QIcon("../resource/in.png")    , */MODE_IN    ));
    addToolBarAction(new QAction(/*QIcon("../resource/out.png")   , */MODE_OUT   ));
    addToolBarAction(new QAction(/*QIcon("../resource/hidden.png"), */MODE_HIDDEN));
    setDefaultToolBarAction(MODE_HIDDEN);

    // setup action
    Editor::getInstance()->addAction(new Open());
    Editor::getInstance()->addAction(new Save());

    // setup menu
    QMenu* fileMenu = new QMenu("File");
    m_ui->menuBar->addMenu(fileMenu);
    fileMenu->addAction(Editor::getInstance()->action(Save::ACTION_SAVE)->action());
    fileMenu->addAction(Editor::getInstance()->action(Open::ACTION_OPEN)->action());

    AnalyzeCircuit* ep = new AnalyzeCircuit();
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
