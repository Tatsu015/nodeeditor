#include "IOTableWidget.h"
#include "AbstractNode.h"
#include "DataBase.h"
#include "DataSetComboBox.h"
#include <QDebug>
#include <QHeaderView>

IOTableWidget::IOTableWidget(QWidget* parent) : QTableWidget(parent) {
  setRowCount(0);
  verticalHeader()->hide();

  QStringList headers = QStringList({"Name", "Value"});
  setColumnCount(headers.count());
  setHorizontalHeaderLabels(headers);
}

IOTableWidget::~IOTableWidget() {
}

void IOTableWidget::addNode(AbstractNode* node) {
  int addedRowCount = rowCount();
  int addRowIndex = addedRowCount + 1;
  setRowCount(addRowIndex);

  setItem(addedRowCount, 0, new QTableWidgetItem(node->name()));
  setCellWidget(addedRowCount, 1, new DataSetComboBox(node->name()));
}

void IOTableWidget::removeNode(AbstractNode* node) {
  for (int row = 0; row < rowCount(); ++row) {
    QTableWidgetItem* tableWidgetItem = item(row, 0);
    if (node->name() == tableWidgetItem->text()) {
      removeRow(row);
    }
  }
}

void IOTableWidget::read() {
  for (int row = 0; row < rowCount(); ++row) {
    QTableWidgetItem* nameWidgetItem = item(row, 0);
    DataSetComboBox* comboItem = dynamic_cast<DataSetComboBox*>(cellWidget(row, 1));

    QString nodeName = nameWidgetItem->text();
    bool value = DataBase::getInstance()->read(nodeName);
    comboItem->setCurrentText(btos(value));
  }
}
