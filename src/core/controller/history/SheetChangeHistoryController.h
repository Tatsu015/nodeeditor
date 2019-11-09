#ifndef SHEETCHANGEHISTORYSTACK_H
#define SHEETCHANGEHISTORYSTACK_H

#include <QList>

class Project;

class SheetChangeHistoryController {
public:
  static SheetChangeHistoryController* getInstance();

  void add(const QString& sheetName);
  QString next() const;
  QString current() const;
  QString previous() const;
  //  void undo(Project* project);
  //  void redo(Project* project);

private:
  QList<QString> m_sheetNameStacks;
  mutable int32_t m_currentPos = -1;

private:
  SheetChangeHistoryController();
  ~SheetChangeHistoryController();
};

#endif // SHEETCHANGEHISTORYSTACK_H
