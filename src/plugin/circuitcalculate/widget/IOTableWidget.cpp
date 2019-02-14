#include "IOTableWidget.h"
#include <QComboBox>
#include <QDebug>
#include <QHeaderView>
#include "AbstractNode.h"

IOTableWidget::IOTableWidget(QWidget* parent) : QTableWidget(parent) {
  setRowCount(0);
  verticalHeader()->hide();

  QStringList headers = QStringList({"Name", "Value"});
  setColumnCount(headers.count());
  setHorizontalHeaderLabels(headers);
}

IOTableWidget::~IOTableWidget() {}

void IOTableWidget::addNode(AbstractNode* node) {
  int addedRowCount = rowCount();
  int addRowIndex = addedRowCount + 1;
  setRowCount(addRowIndex);

  setItem(addedRowCount, 0, new QTableWidgetItem(node->name()));

  QComboBox* comboBox = new QComboBox();
  comboBox->addItems(QStringList({"True", "False"}));
  setCellWidget(addedRowCount, 1, comboBox);
}

void IOTableWidget::removeNode(AbstractNode* node) {
  for (int row = 0; row < rowCount(); ++row) {
    QTableWidgetItem* tableWidgetItem = item(row, 0);
    if (node->name() == tableWidgetItem->text()) {
      removeRow(row);
    }
  }
}
