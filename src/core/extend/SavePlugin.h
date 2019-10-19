#ifndef SavePLUGIN_H
#define SavePLUGIN_H

#include "AbstractPlugin.h"

class SavePlugin : public AbstractPlugin {
public:
  SavePlugin(QObject* parent = nullptr);
  virtual ~SavePlugin();

protected:
  void doInit();

private:
  void save(const QString& filePath);

private slots:
  void onExecuteSave();
  void onExecuteSaveAs();
};

#endif // SavePLUGIN_H
