#include "SheetFactory.h"
#include "FunctionBlockNode.h"
#include "NodeFactory.h"
#include "Sheet.h"

SheetFactory* SheetFactory::getInstance() {
  static SheetFactory s;
  return &s;
}

void SheetFactory::addSheet(Sheet* sheet) {
  m_sheet = sheet;
}

Sheet* SheetFactory::createSheet(const QString& id) {
  Sheet* sheet;
  if (id.isEmpty()) {
    sheet = m_sheet->create();
  } else {
    sheet = m_sheet->create(id);
  }
  static uint32_t index;
  QString name = "Sheet_" + QString::number(++index);
  sheet->setName(name);

  FunctionBlockNode* functionBlockNode = new FunctionBlockNode(sheet);
  NodeFactory::getInstance()->addNode(functionBlockNode);

  return sheet;
}

SheetFactory::SheetFactory() {
}

SheetFactory::~SheetFactory() {
}
