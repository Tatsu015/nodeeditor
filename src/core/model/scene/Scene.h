#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class AbstractNode;
class InNode;
class Connection;
class Port;
class Connector;
class GuideLine;
class SceneObserver;
class Sheet;

class Scene : public QGraphicsScene {
public:
  enum SelectedFilter : bool {
    OnlySelected = true,
    OnlyUnselected = false,
  };

public:
  Scene(QObject* parent = nullptr);
  virtual ~Scene();

  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
  virtual void keyPressEvent(QKeyEvent* event);
  virtual void keyReleaseEvent(QKeyEvent* event);
  virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

  Sheet* sheet() const;
  void setSheet(Sheet* sheet);
  void changeSheet(Sheet* sheet);

  QList<AbstractNode*> findNodes(QPointF scenePos);
  AbstractNode* findNode(const QString& nodeName);
  QList<AbstractNode*> nearTopNodes(const qreal top) const;
  QList<AbstractNode*> nearTopNodes(const qreal top, const SelectedFilter filter) const;
  QList<AbstractNode*> nearBottomNodes(const qreal bottom) const;
  QList<AbstractNode*> nearBottomNodes(const qreal bottom, const SelectedFilter filter) const;
  QList<AbstractNode*> nearRightNodes(const qreal right) const;
  QList<AbstractNode*> nearRightNodes(const qreal right, const SelectedFilter filter) const;
  QList<AbstractNode*> nearLeftNodes(const qreal left) const;
  QList<AbstractNode*> nearLeftNodes(const qreal left, const SelectedFilter filter) const;
  QList<AbstractNode*> selectedNodes() const;

  void addNode(AbstractNode* node);
  void removeNode(AbstractNode* node);

  Connection* findConnection(const QPointF scenePos);
  Connection* findConnection(const QString connectionName);
  QList<Connection*> findConnections(const QPointF scenePos);
  void addConnection(Connection* connection);
  void removeConnection(Connection* connection);

  void addGuideLine(GuideLine* guideLine);
  void clearGuideLine();

  bool existPort(QPointF scenePos);
  Port* findPort(QPointF scenePos);

  void addSceneObserver(SceneObserver* sceneObserver);

  void takeOver(Scene* scene);

private:
  void changeActiveTool(const QPointF nowScenePos);
  Port* findStartPort(QPointF scenePos);
  Port* findEndPort(QPointF scenePos);

  void notifyAdd(AbstractNode* node);
  void notifyRemove(AbstractNode* node);

  void redraw();

private:
  Port* m_startPort = nullptr;
  QVector<GuideLine*> m_guideLines;
  bool m_isControlPressed;
  QVector<SceneObserver*> m_sceneObservers;
  Sheet* m_sheet = nullptr;
};

#endif // SCENE_H
