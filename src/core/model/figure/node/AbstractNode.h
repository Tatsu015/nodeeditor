#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H

#include "Common.h"
#include "Define.h"
#include <QGraphicsPathItem>
#include <QJsonArray>

class Port;
class QGraphicsSimpleTextItem;

class AbstractNode : public QGraphicsPathItem {
public:
  AbstractNode(QGraphicsItem* parent = nullptr);
  virtual ~AbstractNode();

  virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
  virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

  virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value);

  AbstractNode* create();
  virtual AbstractNode* create(const QString& id) = 0;
  void created();

  void setup();

  QString name() const;
  void setName(const QString& name);

  qreal top() const;
  qreal bottom() const;
  qreal right() const;
  qreal left() const;

  QPointF centerOffset() const;

  QList<Port*> ports() const;
  int32_t portCount() const;
  void addPort(Port* port);
  void addInputPort(Port* inputPort);
  void addOutputPort(Port* outputPort);
  bool canAddInputPort() const;
  bool canAddOutputPort() const;
  void removePort(Port* port);
  bool canRemoveInputPort() const;
  bool canRemoveOutputPort() const;

  Port* port(const uint64_t number);
  Port* nearestPort(QPointF scenePos);
  Port* nearestInputPort(QPointF scenePos);
  Port* nearestOutputPort(QPointF scenePos);

  QList<Port*> inputPorts() const;
  QList<Port*> outputPorts() const;
  int32_t inputPortCount() const;
  int32_t outputPortCount() const;

  QList<AbstractNode*> adjastOutNodes();
  QList<AbstractNode*> adjastInNodes();
  QList<AbstractNode*> adjastNodes();

  EPosition portPosition(Port* port);

  QString nodeType() const;
  void setNodeType(const QString& nodeType);

  void redraw();

  IO io() const;

  bool isReplaceable(AbstractNode* target) const;

  void changeColor(const QColor color);
  void resetColor();

  void setNameTextVisible(const bool visible);
  void setIdTextVisible(const bool visible);

  virtual bool execute(QList<bool> args) = 0;

  QString id() const;

  QJsonObject toJsonObject();

private:
  void adjustInputPortPos();
  void adjustOutputPortPos();
  void setupNameText();
  void setupIdText();
  virtual void doSetup();

  bool isInputPortEditable() const;
  bool isOutputPortEditable() const;

  void changeHighlightColor();

protected:
  const static uint32_t WIDTH = 50;
  const static uint32_t HEIGHT = 50;
  const static uint32_t PEN_SIZE = 3;
  const static uint32_t ROUND_RADIUS = 3;
  const static uint32_t PORT_POS_X_OFS = 3;
  const static uint32_t PORT_POS_Y_OFS = 5;

protected:
  QString m_nodeType;
  IO m_io;
  QString m_id = "";
  int32_t m_maxInputPortCount = 1;
  int32_t m_maxOutputPortCount = 1;
  int32_t m_minInputPortCount = 1;
  int32_t m_minOutputPortCount = 1;

private:
  QList<Port*> m_ports;
  QString m_name = "";
  QGraphicsSimpleTextItem* m_nameText = nullptr;
  QGraphicsSimpleTextItem* m_idText = nullptr;
};

#endif // ABSTRACTNODE_H
