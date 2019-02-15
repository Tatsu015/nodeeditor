#include "DataSetComboBox.h"
#include "DataBase.h"
#include "Common.h"

DataSetComboBox::DataSetComboBox(const QString& nodeName, QWidget* parent):
  QComboBox(parent),
  m_nodeName(nodeName)
{
  addItems(QStringList({"true", "false"}));
  connect(this, &DataSetComboBox::currentTextChanged, this, &DataSetComboBox::setData);
  setData("true");
}

DataSetComboBox::~DataSetComboBox()
{
}

void DataSetComboBox::read()
{
  bool value = DataBase::getInstance()->read(m_nodeName);
  setCurrentText(btos(value));
}

void DataSetComboBox::setData(const QString& value)
{
  DataBase::getInstance()->write(m_nodeName, stob(value));
}
