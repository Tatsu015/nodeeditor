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
  virtual QMenu* contextSubMenu(QGraphicsSceneContextMenuEvent* event) const;
  virtual QList<QAction*> contextMenuActions(QGraphicsSceneContextMenuEvent* event) const;

protected:
  virtual void initView(MainWindow* mainWindow, Ui::MainWindow* ui);
  virtual void doInit() = 0;

protected:
  void useContextMenu(const bool isUse);

private:
  bool m_isContextMenuUse = false;
};

#endif // ABSTRACTPLUGIN_H
