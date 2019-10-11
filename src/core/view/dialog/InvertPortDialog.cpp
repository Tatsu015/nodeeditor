#include "InvertPortDialog.h"
#include "AbstractNode.h"
#include "Port.h"
#include "ui_InvertPortDialog.h"
#include <QCheckBox>
#include <QGridLayout>

InvertPortDialog::InvertPortDialog(QWidget* parent) : QDialog(parent), ui(new Ui::InvertPortDialog) {
  ui->setupUi(this);
  m_checkboxLayout = new QGridLayout();
  ui->frame->setLayout(m_checkboxLayout);
}

InvertPortDialog::~InvertPortDialog() {
  delete ui;
}

void InvertPortDialog::setupDialog(const AbstractNode* node) {
  int32_t i = 0;
  m_namePortMaps.clear();
  foreach (Port* port, node->inputPorts()) {
    QString name = "Input Port" + QString::number(i + 1);
    QCheckBox* checkBox = new QCheckBox(name);
    checkBox->setChecked(port->isInvert());
    m_checkboxLayout->addWidget(checkBox, i, 0, 1, 1);
    m_namePortMaps[checkBox] = port;
    ++i;
  }
  int32_t j = 0;
  foreach (Port* port, node->outputPorts()) {
    QString name = "Output Port" + QString::number(j + 1);
    QCheckBox* checkBox = new QCheckBox(name);
    checkBox->setChecked(port->isInvert());
    m_checkboxLayout->addWidget(checkBox, j, 1, 1, 1);
    m_namePortMaps[checkBox] = port;
    ++j;
  }
}

QList<Port*> InvertPortDialog::invertPorts() const {
  QList<Port*> ports;
  foreach (QCheckBox* checkBox, m_namePortMaps.keys()) {
    if (checkBox->isChecked()) {
      ports << m_namePortMaps[checkBox];
    }
  }
  return ports;
}
