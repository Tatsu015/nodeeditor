#ifndef CONNECTION_H
#define CONNECTION_H

#include <QGraphicsPathItem>

class Port;
class Connector;

class Connection : public QGraphicsPathItem {
public:
  Connection(QGraphicsItem* parent = nullptr);
  virtual ~Connection();

  virtual Connection* create();

  void setStartPos(const QPointF& startPos);
  void setEndPos(const QPointF& endPos);

  void redraw();
  void redraw(Port* startPort, Port* endPort);
  void redraw(Port* startPort, QPointF endScenePos);

  Port* startPort() const;
  void setStartPort(Port* startPort);
  void removeStartPort();
  Port* endPort() const;
  void setEndPort(Port* endPort);
  void removeEndPort();
  Port* oppositeSidePort(Port* port);

  void setStartConnector(Connector* startConnector);
  void removeStartConnector();
  void setEndConnector(Connector* endConnector);
  void removeEndConnector();
  void addBranchConnector(Connector* connector, QPointF scenePos);
  void removeBranchConnector(Connector* connector);

  QString name() const;
  void setName(const QString& name);

  QString connectionType() const;

protected:
  const static QColor LINE_COLOR;
  const static uint32_t PEN_SIZE;

private:
  QString m_name = "";
  QString m_connectionType = "";
  QPointF m_startPos;
  QPointF m_endPos;
  Port* m_startPort = nullptr;
  Port* m_endPort = nullptr;

  Connector* m_startConnector = nullptr;
  Connector* m_endConnector = nullptr;

  QList<Connector*> m_branchConnectors;
};

#endif // CONNECTION_H
