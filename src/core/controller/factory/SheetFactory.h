#ifndef SHEETFACTORY_H
#define SHEETFACTORY_H

#include <QMap>
#include <QString>

class Sheet;

class SheetFactory {
public:
  static SheetFactory* getInstance();

  void addSheetBase(Sheet* sheet);
  Sheet* createSheet(const QString& name, const QString& id);
  Sheet* createSheet();

private:
  Sheet* m_sheetBase = nullptr;

private:
  SheetFactory();
  ~SheetFactory();
};

#endif // SHEETFACTORY_H
