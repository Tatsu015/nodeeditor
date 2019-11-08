#include "SheetFactory.h"
#include "FunctionBlockNode.h"
#include "NodeFactory.h"
#include "SerialNumberNamePublisher.h"
#include "Sheet.h"

SheetFactory* SheetFactory::getInstance() {
  static SheetFactory s;
  return &s;
}

void SheetFactory::addSheet(Sheet* sheet) {
  m_sheet = sheet;
}

Sheet* SheetFactory::createSheet(const QString& name, const QString& id) {
  Sheet* sheet;
  sheet = m_sheet->create(id);

  sheet->setName(name);

  FunctionBlockNode* functionBlockNode = new FunctionBlockNode(sheet);
  NodeFactory::getInstance()->addNode(functionBlockNode);

  return sheet;
}

Sheet* SheetFactory::createSheet(const QStringList existNames, const QString& id) {
  Sheet* sheet;
  if (id.isEmpty()) {
    sheet = m_sheet->create();
  } else {
    sheet = m_sheet->create(id);
  }
  QString name = SerialNumberNamePublisher::getInstance()->createName(existNames, "Sheet");
  sheet->setName(name);

  FunctionBlockNode* functionBlockNode = new FunctionBlockNode(sheet);
  NodeFactory::getInstance()->addNode(functionBlockNode);

  return sheet;
}

SheetFactory::SheetFactory() {
}

SheetFactory::~SheetFactory() {
}
