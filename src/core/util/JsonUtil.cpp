#include "JsonUtil.h"
#include "Define.h"
#include <QJsonObject>

QJsonArray pointFsToJson(QList<QPointF> points) {
  QJsonArray pointsJsonArray;
  foreach (QPointF point, points) {
    QJsonObject pointObject;
    pointObject[X] = point.x();
    pointObject[Y] = point.y();
    pointsJsonArray.append(pointObject);
  }
  return pointsJsonArray;
}

QList<QPointF> jsonToPointFs(QJsonArray jsonArray) {
  QList<QPointF> points;
  foreach (QJsonValue value, jsonArray) {
    QPointF point(value[X].toInt(), value[Y].toInt());
    points << point;
  }
  return points;
}
