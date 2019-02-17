#ifndef ABSTRACTPLUGIN_H
#define ABSTRACTPLUGIN_H

#include <QAction>
#include <QObject>

class QMenuBar;
class MainWindow;
namespace Ui {
class MainWindow;
}

class AbstractPlugin : public QObject {
  Q_OBJECT

 public:
  AbstractPlugin(QObject* parent = nullptr);
  virtual ~AbstractPlugin();

  void init(MainWindow* mainWindow, Ui::MainWindow* ui);
  virtual void reset();

 protected:
  virtual void initView(MainWindow* mainWindow, Ui::MainWindow* ui);
  virtual void doInit() = 0;
};

#endif  // ABSTRACTPLUGIN_H
