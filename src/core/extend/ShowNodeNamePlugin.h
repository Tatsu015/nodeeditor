#ifndef SHOWNODENAMEPLUGIN_H
#define SHOWNODENAMEPLUGIN_H

#include "AbstractPlugin.h"

class ShowNameViewPlugin : public AbstractPlugin {
public:
  ShowNameViewPlugin(QObject* parent = nullptr);
  virtual ~ShowNameViewPlugin();

protected:
  void doInit();

private slots:
  void onExecute();

private:
  QAction* m_action = nullptr;
};

#endif // SHOWNODENAMEPLUGIN_H
