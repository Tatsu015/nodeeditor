#ifndef CONNECTION_H
#define CONNECTION_H

#include <QGraphicsPathItem>

class Port;
class Connector;

class Connection : public QGraphicsPathItem {
 public:
  Connection(QGraphicsItem* parent = nullptr);
  virtual ~Connection();

  Connection* create();

  void setStartPos(const QPointF& startPos);
  void setEndPos(const QPointF& endPos);

  void setStartPort(Port* startPort);
  void setEndPort(Port* endPort);

  void redraw();
  void redraw(Port* startPort, Port* endPort);
  void redraw(Port* startPort, QPointF endScenePos);

  Port* startPort() const;
  Port* endPort() const;

  void removeStartPort();
  void removeEndPort();

  Port* oppositeSidePort(Port* port);
  void addConnector(Connector* connector);

  QString name() const;
  void setName(const QString& name);

  QString connectionType() const;

 protected:
  const static QColor LINE_COLOR;
  const static uint32_t PEN_SIZE = 3;

 private:
  QString m_name = "";
  QString m_connectionType = "";
  QPointF m_startPos;
  QPointF m_endPos;
  Port* m_startPort = nullptr;
  Port* m_endPort = nullptr;

  QList<Connector*> m_connectors;
};

#endif  // CONNECTION_H
