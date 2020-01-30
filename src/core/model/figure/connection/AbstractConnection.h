#ifndef ABSTRACTCONNECTION_H
#define ABSTRACTCONNECTION_H

#include "Define.h"
#include <QGraphicsPathItem>

class Port;
class Connector;
class EdgeHandle;

class AbstractConnection : public QGraphicsPathItem {
public:
  enum Direction : uint32_t { Vertical, Horizon, Other };
  enum ConnectionStyle : uint32_t { Connected, Connectable, Connecting };

public:
  AbstractConnection(QGraphicsItem* parent = nullptr);
  virtual ~AbstractConnection();

  virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);

  AbstractConnection* create();
  virtual AbstractConnection* create(const QString& id) = 0;

  QPixmap pixmap() const;

  QPointF startPos() const;
  void setStartPos(const QPointF& startPos);
  QPointF endPos() const;
  void setEndPos(const QPointF& endPos);

  virtual void redraw() = 0;
  void redraw(Port* startPort, Port* endPort);
  void redraw(Port* startPort, QPointF endScenePos);

  Port* startPort() const;
  void setStartPort(Port* startPort);
  bool hasStartPort() const;
  void removeStartPort();
  Port* endPort() const;
  void setEndPort(Port* endPort);
  bool hasEndPort() const;
  void removeEndPort();
  Port* oppositeSidePort(Port* port);
  Port* inputPort() const;
  bool hasInputPort() const;
  Port* outputPort() const;
  bool hasOutputPort() const;
  int32_t areaIndex(QPointF pos, QSizeF searchSize = QSizeF(3, 3)) const;
  QPointF closeCenter(QPointF pos, QSizeF searchSize = QSizeF(3, 3));
  Direction direction(QPointF pos, QSizeF searchSize = QSizeF(3, 3)) const;
  Edge whichEdge(Port* port);

  Connector* startConnector() const;
  void setStartConnector(Connector* startConnector);
  void removeStartConnector();
  bool hasStartConnector() const;

  Connector* endConnector() const;
  void setEndConnector(Connector* endConnector);
  void removeEndConnector();
  bool hasEndConnector() const;

  void addBranchConnector(Connector* connector);
  void removeBranchConnector(Connector* connector);
  QList<Connector*> branchConnectors() const;
  void addVertex(QPointF vertex);
  void addVertexes(QList<QPointF> vertex);
  QList<QPointF> vertexes() const;

  QList<AbstractConnection*> connectedConnections();

  QString name() const;
  void setName(const QString& name);

  QString connectionType() const;

  QString id() const;

  void changeConnectionStyle(const ConnectionStyle style);

  virtual QJsonObject toJsonObj() = 0;

private:
  QVector<QPointF> points() const;
  QList<AbstractConnection*> connectedConnections(const Connector* excludeConnector);

protected:
  const static uint32_t PEN_SIZE;

protected:
  QString m_id = "";
  QString m_name = "";
  QString m_connectionType = "";
  QString m_pixmapFilePath = "";
  QPointF m_startPos;
  QPointF m_endPos;
  Port* m_startPort = nullptr;
  Port* m_endPort = nullptr;
  EdgeHandle* m_startEdgeHandle = nullptr;
  EdgeHandle* m_endEdgeHandle = nullptr;

  Connector* m_startConnector = nullptr;
  Connector* m_endConnector = nullptr;

  QList<Connector*> m_branchConnectors;

  QList<QPointF> m_vertexes;
};

#endif // ABSTRACTCONNECTION_H
