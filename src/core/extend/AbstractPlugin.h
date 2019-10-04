#ifndef ABSTRACTPLUGIN_H
#define ABSTRACTPLUGIN_H

#include <QAction>
#include <QObject>

class QMenuBar;
class QGraphicsSceneContextMenuEvent;
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

  bool isContextMenuUse() const;
  virtual QList<QAction*> contextMenuActions(QGraphicsSceneContextMenuEvent* event) const;

protected:
  virtual void initView(MainWindow* mainWindow, Ui::MainWindow* ui);
  virtual void doInit() = 0;

protected:
  bool m_isContextMenuUse = false;
};

#endif // ABSTRACTPLUGIN_H
