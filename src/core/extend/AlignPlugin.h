#ifndef AlignPlugin_H
#define AlignPlugin_H

#include "AbstractPlugin.h"

class AlignPlugin : public AbstractPlugin {
public:
  AlignPlugin(QObject* parent = nullptr);
  virtual ~AlignPlugin();

  virtual QList<QAction*> contextMenuActions(QGraphicsSceneContextMenuEvent* event) const;

protected:
  void doInit();

private slots:
  void onExecuteAlignLeft();
  void onExecuteAlignRight();
  void onExecuteAlignTop();
  void onExecuteAlignBottom();

private:
  QAction* m_alignLeftAction = nullptr;
  QAction* m_alignRightAction = nullptr;
  QAction* m_alignTopAction = nullptr;
  QAction* m_alignBottomAction = nullptr;
};

#endif // AlignPlugin_H
