#ifndef SheetFactory_H
#define SheetFactory_H

#include <QMap>
#include <QString>

class Sheet;

class SheetFactory {
public:
  static SheetFactory* getInstance();

  void addSheet(Sheet* sheet);
  Sheet* createSheet(const QString& name, const QString& id);
  Sheet* createSheet(const QStringList existNames, const QString& id = "");

private:
  Sheet* m_sheet = nullptr;

private:
  SheetFactory();
  ~SheetFactory();
};

#endif // SheetFactory_H
