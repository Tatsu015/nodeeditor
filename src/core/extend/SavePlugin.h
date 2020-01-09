#ifndef SAVEPLUGIN_H
#define SAVEPLUGIN_H

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

#endif // SAVEPLUGIN_H
