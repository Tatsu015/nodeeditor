#ifndef GUIDELINE_H
#define GUIDELINE_H

#include <QGraphicsLineItem>

class GuideLine : public QGraphicsLineItem {
public:
  GuideLine(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem* parent = nullptr);
  virtual ~GuideLine();

protected:
  const static QColor LINE_COLOR;
  const static uint32_t PEN_SIZE = 1;
};

#endif // GUIDELINE_H
