#ifndef NODE_H
#define NODE_H

#include "Common.h"
#include "Define.h"
#include <QGraphicsPathItem>

class Port;
class QGraphicsSimpleTextItem;

class AbstractNode : public QGraphicsPathItem {
public:
  AbstractNode(QGraphicsItem* parent = nullptr);
  virtual ~AbstractNode();

  virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
  virtual void hoverMoveEvent(QGraphicsSceneHoverEvent* event);
  virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

  virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value);

  virtual AbstractNode* create() = 0;

  QString name() const;
  void setName(const QString& name);

  qreal top() const;
  qreal bottom() const;
  qreal right() const;
  qreal left() const;

  QPointF centerOffset() const;

  void setupNameText();

  QList<Port*> ports() const;
  void addPort(Port* port);
  Port* port(const uint64_t number);

  QList<AbstractNode*> adjastOutNodes();
  QList<AbstractNode*> adjastInNodes();
  QList<AbstractNode*> adjastNodes();

  EPosition portPosition(Port* port);

  QString nodeType() const;

  void redraw();

  IO io() const;

  void changeColor(const QColor color);
  void resetColor();

  void setNameTextVisible(const bool visible);

  virtual bool execute(QList<bool> args) = 0;

protected:
  const static QColor FILL_COLOR;
  const static QColor LINE_COLOR;
  const static uint32_t WIDTH = 50;
  const static uint32_t HEIGHT = 50;
  const static uint32_t PEN_SIZE = 3;
  const static uint32_t ROUND_RADIUS = 3;
  const static uint32_t PORT_POS_X_OFS = 2;
  const static uint32_t PORT_POS_Y_OFS = 5;

protected:
  QString m_nodeType;
  IO m_io;

private:
  QList<Port*> m_ports;
  QString m_name;
  QGraphicsSimpleTextItem* m_nameText = nullptr;
};

#endif // NODE_H
