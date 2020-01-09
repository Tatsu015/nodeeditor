#ifndef CUTPLUGIN_H
#define CUTPLUGIN_H

#include "AbstractPlugin.h"

class CutPlugin : public AbstractPlugin {
public:
  CutPlugin(QObject* parent = nullptr);
  virtual ~CutPlugin();

  virtual QList<QAction*> contextMenuActions(QGraphicsSceneContextMenuEvent* event) const;

protected:
  void doInit();

private slots:
  void onExecute();

private:
  QAction* m_action = nullptr;
};

#endif // CUTPLUGIN_H
