#ifndef SavePLUGIN_H
#define SavePLUGIN_H

#include "AbstractPlugin.h"

class SavePlugin : public AbstractPlugin {
 public:
  SavePlugin(QObject* parent = nullptr);
  virtual ~SavePlugin();

 protected:
  void doInit();

 private slots:
  void onExecute();
};

#endif  // SavePLUGIN_H
