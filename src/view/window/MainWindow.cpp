#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Editor.h"
#include "NodeFactory.h"
#include "ConnectionFactory.h"
#include "Connection.h"
#include "HiddenNode.h"
#include "InNode.h"
#include "OutNode.h"
#include "SaveAction.h"
#include "OpenAction.h"
#include "Define.h"
#include "Builder.h"


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

    // setup action
    Editor::getInstance()->addAction(new OpenAction());
    Editor::getInstance()->addAction(new SaveAction());

    Builder::getInstance()->build(this, m_ui);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

