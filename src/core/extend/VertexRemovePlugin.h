#ifndef VERTEXDELETEPLUGIN_H
#define VERTEXDELETEPLUGIN_H

#include "AbstractPlugin.h"

class VertexHandle;

class VertexRemovePlugin : public AbstractPlugin {
public:
  VertexRemovePlugin(QObject* parent = nullptr);
  virtual ~VertexRemovePlugin();

  virtual QList<QAction*> contextMenuActions(QGraphicsSceneContextMenuEvent* event) const;

protected:
  void doInit();

private slots:
  void onExecute();

private:
  QAction* m_action = nullptr;
  mutable VertexHandle* m_deleteVertexHandleCache = nullptr;
};

#endif // VERTEXDELETEPLUGIN_H
