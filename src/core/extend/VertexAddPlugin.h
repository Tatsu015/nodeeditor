#ifndef VERTEXADDPLUGIN_H
#define VERTEXADDPLUGIN_H

#include "AbstractPlugin.h"

class VertexHandle;
class AbstractConnection;

class VertexAddPlugin : public AbstractPlugin {
public:
  VertexAddPlugin(QObject* parent = nullptr);
  virtual ~VertexAddPlugin();

  virtual QList<QAction*> contextMenuActions(QGraphicsSceneContextMenuEvent* event) const;

protected:
  void doInit();

private slots:
  void onExecute();

private:
  QAction* m_action = nullptr;
  mutable AbstractConnection* m_connectionleCache = nullptr;
  mutable QPointF m_pos;
};

#endif // VERTEXADDPLUGIN_H
