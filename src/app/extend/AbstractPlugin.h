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

  void init(Ui::MainWindow* ui);

 protected:
  virtual void initView(Ui::MainWindow* ui);
  virtual void doInit() = 0;
};

#endif  // ABSTRACTPLUGIN_H
