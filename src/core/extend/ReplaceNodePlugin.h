#ifndef REPLACENODEPLUGIN_H
#define REPLACENODEPLUGIN_H

#include "AbstractPlugin.h"

class AbstractNode;

class ReplaceNodePlugin : public AbstractPlugin {
public:
  ReplaceNodePlugin(QObject* parent = nullptr);
  virtual ~ReplaceNodePlugin();

  virtual QList<QAction*> contextMenuActions(QGraphicsSceneContextMenuEvent* event) const;

protected:
  void doInit();

private slots:
  void onExecute();

private:
  QAction* m_action = nullptr;
  mutable QStringList m_nameCache;
  mutable AbstractNode* m_replaceNodeCache = nullptr;
};

#endif // REPLACENODEPLUGIN_H
