#ifndef JUMPSHEETPLUGIN_H
#define JUMPSHEETPLUGIN_H

#include "AbstractPlugin.h"
#include <QString>

class FunctionBlockNode;

class JumpSheetPlugin : public AbstractPlugin {
public:
  JumpSheetPlugin(QObject* parent = nullptr);
  virtual ~JumpSheetPlugin();

  virtual QList<QAction*> contextMenuActions(QGraphicsSceneContextMenuEvent* event) const;

protected:
  void doInit();

private slots:
  void onExecute();

private:
  QAction* m_action = nullptr;
  mutable FunctionBlockNode* m_targetFunctionBlockNode = nullptr;
};

#endif // JUMPSHEETPLUGIN_H
