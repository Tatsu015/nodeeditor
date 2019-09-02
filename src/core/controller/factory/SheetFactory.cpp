#include "SheetFactory.h"
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
  sheet->setName("Sheet_" + QString::number(++index));

  return sheet;
}

SheetFactory::SheetFactory() {
}

SheetFactory::~SheetFactory() {
}
