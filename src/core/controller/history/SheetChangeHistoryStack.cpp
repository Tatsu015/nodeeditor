#include "SheetChangeHistoryStack.h"
#include "Project.h"

SheetChangeHistoryController* SheetChangeHistoryController::getInstance() {
  static SheetChangeHistoryController s;
  return &s;
}

void SheetChangeHistoryController::add(const QString& sheetName) {
  if (m_currentPos < m_sheetNameStacks.count() - 1) {
    QStringList l;
    l = m_sheetNameStacks.mid(0, m_currentPos + 1);
    m_sheetNameStacks.clear();
    m_sheetNameStacks << l;
  }
  ++m_currentPos;
  m_sheetNameStacks << sheetName;
}

QString SheetChangeHistoryController::previous() const {
  int32_t nextPos = m_currentPos - 1;
  if (0 > nextPos) {
    return "";
  }
  m_currentPos = nextPos;
  return m_sheetNameStacks[m_currentPos];
}

QString SheetChangeHistoryController::current() const {
  return m_sheetNameStacks[m_currentPos];
}

QString SheetChangeHistoryController::next() const {
  int32_t nextPos = m_currentPos + 1;
  if (nextPos > m_sheetNameStacks.count() - 1) {
    return "";
  }
  m_currentPos = nextPos;
  return m_sheetNameStacks[m_currentPos];
}

// void SheetChangeHistoryController::undo(Project* project) {
//  int32_t nextPos = m_currentPos - 1;
//  if (nextPos > m_sheetNameStacks.count()) {
//    return;
//  }
//  QString sheetName = m_sheetNameStacks[nextPos];
//  project->changeActiveSheet(sheetName);
//}

// void SheetChangeHistoryController::redo(Project* project) {
//  int32_t nextPos = m_currentPos + 1;
//  if (nextPos > m_sheetNameStacks.count()) {
//    return;
//  }
//  QString sheetName = m_sheetNameStacks[nextPos];
//  project->changeActiveSheet(sheetName);
//}

SheetChangeHistoryController::SheetChangeHistoryController() {
}

SheetChangeHistoryController::~SheetChangeHistoryController() {
}
