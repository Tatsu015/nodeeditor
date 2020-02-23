#include "DebugControlWidget.h"
#include "ui_DebugControlWidget.h"

DebugControlWidget::DebugControlWidget(QWidget* parent) : QWidget(parent), m_ui(new Ui::DebugControlWidget) {
  m_ui->setupUi(this);
  m_ui->startDebugButton->setIcon(QIcon("../resource/debug.png"));
  m_ui->stepOverButton->setIcon(QIcon("../resource/downarrow.png"));
  m_ui->stopDebugButton->setIcon(QIcon("../resource/stop.png"));
  tearDown();
}

DebugControlWidget::~DebugControlWidget() {
  delete m_ui;
}

Ui::DebugControlWidget* DebugControlWidget::ui() const {
  return m_ui;
}

void DebugControlWidget::setup() {
  m_ui->startDebugButton->setEnabled(false);
  m_ui->stepOverButton->setEnabled(true);
  m_ui->stopDebugButton->setEnabled(true);
}

void DebugControlWidget::tearDown() {
  m_ui->startDebugButton->setEnabled(true);
  m_ui->stepOverButton->setEnabled(false);
  m_ui->stopDebugButton->setEnabled(false);
}
