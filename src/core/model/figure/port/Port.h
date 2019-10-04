#ifndef PORT_H
#define PORT_H

#include "Define.h"
#include <QGraphicsPathItem>

class Connection;
class Port;
class AbstractNode;

class Port : public QGraphicsPathItem {
public:
  Port(IO io, uint32_t number, QGraphicsItem* parent = nullptr, bool isInvert = false);
  virtual ~Port();

  QRectF boundingRect() const override;

  Port* create(IO io, uint32_t number, QGraphicsItem* parent);

  QPointF centerScenePos();
  QPointF endOfPortPos();
  QPointF endOfNodePos();
  void addConnection(Connection* connection);
  void removeConnection(Connection* connection);

  QList<Connection*> connections() const;

  IO io() const;
  uint32_t number() const;
  AbstractNode* parentNode() const;

  void redraw();
  QString portType() const;

  bool canConnect() const;

  void invert(const bool isInvert);
  bool isInvert() const;

protected:
  const static uint32_t WIDTH = 13;
  const static uint32_t HEIGHT = 13;
  const static uint32_t LINE_WIDTH = 12;
  const static uint32_t LINE_HEIGHT = 3;
  const static uint32_t LINE_PEN_SIZE = 0;
  const static uint32_t ELLIPSE_RADIUS = 11;
  const static uint32_t ELLIPSE_PEN_SIZE = 3;

private:
  QString m_portType;
  QString m_name;
  QList<Connection*> m_connections;
  AbstractNode* m_parentNode = nullptr;
  IO m_io;
  uint32_t m_number;
  bool m_isInvert = false;
  int32_t m_maxConnectableCount = 1;
};

#endif // PORT_H
