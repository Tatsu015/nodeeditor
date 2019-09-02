#include "FigureNamePublisher.h"
#include "Sheet.h"
#include <QDebug>

const static QString SEPALATOR = "_";

FigureNamePublisher* FigureNamePublisher::getInstance() {
  static FigureNamePublisher s;
  return &s;
}

QString FigureNamePublisher::createName(const Sheet* sheet, const QString& figureBaseName) {
  uint64_t id = 1;
  QString newName = figureBaseName + SEPALATOR + QString::number(id);
  while (sheet->contain(newName)) {
    newName = figureBaseName + SEPALATOR + QString::number(++id);
  }
  return newName;
}

FigureNamePublisher::FigureNamePublisher() {
}

FigureNamePublisher::~FigureNamePublisher() {
}
