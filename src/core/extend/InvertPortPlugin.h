#ifndef InvertPortPlugin_H
#define InvertPortPlugin_H

#include "AbstractPlugin.h"

class InvertPortPlugin : public AbstractPlugin {
public:
  InvertPortPlugin(QObject* parent = nullptr);
  virtual ~InvertPortPlugin();

protected:
  void doInit();

private slots:
  void onExecute();

private:
  QAction* m_action = nullptr;
};

#endif // InvertPortPlugin_H
