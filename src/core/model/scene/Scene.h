#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class AbstractNode;
class FunctionBlockNode;
class InNode;
class AbstractConnection;
class Port;
class Connector;
class EdgeHandle;
class VertexHandle;
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
  void removeSheet();

  QList<AbstractNode*> findNodes(QPointF scenePos);
  AbstractNode* findNode(const QString& nodeName);
  AbstractNode* findNode(QPointF scenePos);
  FunctionBlockNode* findFunctionBlockNode(QPointF scenePos);
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

  AbstractConnection* findConnection(const QPointF scenePos, AbstractConnection* exclude);
  AbstractConnection* findConnection(const QString connectionName);
  QList<AbstractConnection*> findConnections(const QPointF scenePos, AbstractConnection* tmponnection);
  void addConnection(AbstractConnection* connection);
  void removeConnection(AbstractConnection* connection);
  QList<AbstractConnection*> selectedConnections() const;

  void addGuideLine(GuideLine* guideLine);
  void clearGuideLine();

  bool existPort(QPointF scenePos);
  Port* findPort(QPointF scenePos, bool penetrate = true);

  EdgeHandle* findEdgeHandle(QPointF scenePos, bool penetrate = true);
  VertexHandle* findVertexHandle(QPointF scenePos, bool penetrate = true);

  void addSceneObserver(SceneObserver* sceneObserver);

  void takeOver(Scene* scene);

private:
  void changeActiveTool(QGraphicsSceneMouseEvent* event);
  Port* findStartPort(QPointF scenePos);
  Port* findEndPort(QPointF scenePos);

  void notifyAdd(AbstractNode* node);
  void notifyRemove(AbstractNode* node);

  void showDefaultText();
  void hideDefaultText();

  void redraw();

private:
  Port* m_startPort = nullptr;
  QVector<GuideLine*> m_guideLines;
  QVector<SceneObserver*> m_sceneObservers;
  Sheet* m_sheet = nullptr;
  QGraphicsTextItem* m_defaultText = nullptr;
};

#endif // SCENE_H
