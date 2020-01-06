#ifndef JSONUTIL_H
#define JSONUTIL_H

#include <QJsonArray>
#include <QList>
#include <QPointF>

extern QJsonArray pointFsToJson(QList<QPointF> points);
extern QList<QPointF> jsonToPointFs(QJsonArray jsonArray);

#endif // JSONUTIL_H
