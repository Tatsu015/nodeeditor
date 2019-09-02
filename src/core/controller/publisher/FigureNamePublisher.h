#ifndef NAMEPUBLISHER_H
#define NAMEPUBLISHER_H

#include <QMap>
#include <QString>

class Sheet;

class FigureNamePublisher {
public:
  static FigureNamePublisher* getInstance();

  QString createName(const Sheet* sheet, const QString& figureBaseName);

private:
  FigureNamePublisher();
  ~FigureNamePublisher();
};

#endif // NAMEPUBLISHER_H
