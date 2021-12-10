#include "SheetFactory.h"
#include "FunctionBlockNode.h"
#include "NodeFactory.h"
#include "SerialNumberNamePublisher.h"
#include "Sheet.h"

SheetFactory* SheetFactory::getInstance() {
  static SheetFactory s;
  return &s;
}

void SheetFactory::addSheetBase(Sheet* sheet) {
  m_sheetBase = sheet;
}

Sheet* SheetFactory::createSheet(const QString& name, const QString& id) {
  Sheet* sheet;
  sheet = m_sheetBase->create(name, id);

  sheet->setName(name);

  FunctionBlockNode* functionBlockNode = new FunctionBlockNode(sheet);
  NodeFactory::getInstance()->addNode(functionBlockNode);

  return sheet;
}

Sheet* SheetFactory::createSheet() {
  Sheet* sheet = m_sheetBase->create();

  FunctionBlockNode* functionBlockNode = new FunctionBlockNode(sheet);
  NodeFactory::getInstance()->addNode(functionBlockNode);

  return sheet;
}

SheetFactory::SheetFactory() {
}

SheetFactory::~SheetFactory() {
}
