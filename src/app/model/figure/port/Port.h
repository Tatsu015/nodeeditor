#ifndef PORT_H
#define PORT_H

#include <QGraphicsPathItem>
#include "Define.h"

class Connection;
class Port;
class AbstractNode;

class Port : public QGraphicsPathItem {
 public:
  Port(IO io, uint32_t number, QGraphicsItem* parent = nullptr);
  virtual ~Port();

  Port* create(IO io, uint32_t number, QGraphicsItem* parent);

  QPointF centerScenePos();
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

 protected:
  const static uint32_t WIDTH = 12;
  const static uint32_t HEIGHT = 3;
  const static QColor FILL_COLOR;
  const static QColor LINE_COLOR;
  const static uint32_t PEN_SIZE = 0;

 private:
  QString m_portType;
  QString m_name;
  QList<Connection*> m_connections;
  AbstractNode* m_parentNode = nullptr;
  IO m_io;
  uint32_t m_number;
};

#endif  // PORT_H
