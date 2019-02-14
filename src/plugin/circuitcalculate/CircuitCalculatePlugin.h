#ifndef CircuitCalculatePLUGIN_H
#define CircuitCalculatePLUGIN_H

#include "AbstractPlugin.h"

class CircuitCalculatePlugin : public AbstractPlugin {
 public:
  CircuitCalculatePlugin();
  virtual ~CircuitCalculatePlugin();

 protected:
  virtual void initView(MainWindow* mainWindow, Ui::MainWindow* ui);
  void doInit();

 private slots:
  void onExecute();
};

#endif  // CircuitCalculatePLUGIN_H
