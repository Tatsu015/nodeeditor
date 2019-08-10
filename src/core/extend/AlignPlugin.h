#ifndef AlignPlugin_H
#define AlignPlugin_H

#include "AbstractPlugin.h"

class AlignPlugin : public AbstractPlugin {
public:
  AlignPlugin(QObject* parent = nullptr);
  virtual ~AlignPlugin();

protected:
  void doInit();

private slots:
  void onExecuteAlignLeft();
  void onExecuteAlignRight();
  void onExecuteAlignTop();
  void onExecuteAlignBottom();
};

#endif // AlignPlugin_H
