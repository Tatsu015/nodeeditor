#ifndef PORT_H
#define PORT_H

#include "Define.h"
#include <QGraphicsPathItem>

class Connection;
class Port;
class AbstractNode;

class Port : public QGraphicsPathItem {
public:
  Port(IO io, uint32_t number, QGraphicsItem* parent = nullptr);
  virtual ~Port();

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

  QString name() const;
  void setName(const QString& name);

  bool canConnect() const;

  void invert();
  bool isInvert() const;

protected:
  const static uint32_t LINE_WIDTH = 12;
  const static uint32_t LINE_HEIGHT = 3;
  const static QColor LINE_FILL_COLOR;
  const static QColor LINE_COLOR;
  const static uint32_t LINE_PEN_SIZE = 0;
  const static uint32_t ELLIPSE_RADIUS = 10;
  const static QColor ELLIPSE_FILL_COLOR;
  const static QColor ELLIPSE_COLOR;
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
