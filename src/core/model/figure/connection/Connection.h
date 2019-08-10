#ifndef CONNECTION_H
#define CONNECTION_H

#include <QGraphicsPathItem>

class Port;
class Connector;

class Connection : public QGraphicsPathItem {
public:
  enum Direction { Vertical, Horizon, Other };

public:
  Connection(QGraphicsItem* parent = nullptr);
  virtual ~Connection();

  virtual Connection* create();

  QPointF startPos() const;
  void setStartPos(const QPointF& startPos);
  QPointF endPos() const;
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
  QVector<QPointF> points() const;
  int32_t areaIndex(QPointF pos, QSizeF searchSize = QSizeF(3, 3)) const;
  QPointF closeCenter(QPointF pos, QSizeF searchSize = QSizeF(3, 3));
  Direction direction(QPointF pos, QSizeF searchSize = QSizeF(3, 3)) const;

  void setStartConnector(Connector* startConnector);
  void removeStartConnector();
  Connector* endConnector() const;
  void setEndConnector(Connector* endConnector);
  void removeEndConnector();
  void addBranchConnector(Connector* connector);
  void removeBranchConnector(Connector* connector);
  QList<Connector*> branchConnectors() const;

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

  Connector* m_endConnector = nullptr;

  QList<Connector*> m_branchConnectors;
};

#endif // CONNECTION_H
