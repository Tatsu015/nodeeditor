#include "GuideLine.h"
#include <QPen>

const QColor GuideLine::LINE_COLOR = QColor(255, 165, 0);

GuideLine::GuideLine(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem* parent)
    : QGraphicsLineItem(x1, y1, x2, y2, parent) {
  QPen pen = QPen(QBrush(LINE_COLOR), PEN_SIZE, Qt::DashLine);
  setPen(pen);
}

GuideLine::~GuideLine() {
}
