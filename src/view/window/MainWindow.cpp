#include "MainWindow.h"
#include "AnalyzeCircuitAction.h"
#include "AndNode.h"
#include "Builder.h"
#include "Connection.h"
#include "ConnectionFactory.h"
#include "Editor.h"
#include "InNode.h"
#include "NodeFactory.h"
#include "OpenAction.h"
#include "OutNode.h"
#include "SaveAction.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
  m_ui->setupUi(this);

  Editor::getInstance()->setGraphicsView(m_ui->graphicsView);
  Editor::getInstance()->init();

  NodeFactory::getInstance()->addNode(new InNode());
  NodeFactory::getInstance()->addNode(new OutNode());
  NodeFactory::getInstance()->addNode(new AndNode());

  ConnectionFactory::getInstance()->addConnection(new Connection());

  // setup action
  Editor::getInstance()->addAction(new OpenAction());
  Editor::getInstance()->addAction(new SaveAction());
  Editor::getInstance()->addAction(new AnalyzeCircuitAction());

  Builder::getInstance()->build(this, m_ui);
}

MainWindow::~MainWindow() { delete m_ui; }
