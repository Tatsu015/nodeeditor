#include "JsonUtil.h"
#include "Define.h"
#include <QJsonObject>

QJsonArray pointFsToJson(QList<QPointF> points) {
  QJsonArray pointsJsonArray;
  foreach (QPointF point, points) {
    QJsonObject pointObject;
    pointObject[JSON_X] = point.x();
    pointObject[JSON_Y] = point.y();
    pointsJsonArray.append(pointObject);
  }
  return pointsJsonArray;
}

QList<QPointF> jsonToPointFs(QJsonArray jsonArray) {
  QList<QPointF> points;
  foreach (QJsonValue value, jsonArray) {
    QPointF point(value[JSON_X].toInt(), value[JSON_Y].toInt());
    points << point;
  }
  return points;
}
