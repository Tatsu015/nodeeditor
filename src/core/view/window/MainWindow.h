#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

class Scene;
class QAction;
class QToolButton;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

protected:
  virtual void keyPressEvent(QKeyEvent* event);
  virtual void keyReleaseEvent(QKeyEvent* event);

private:
  struct ToolBarAction {
    QAction* m_action = nullptr;
    QToolButton* m_button = nullptr;
  };

private:
  Ui::MainWindow* m_ui = nullptr;
  QMap<QString, ToolBarAction*> m_toolBarActions;
};

#endif // MAINWINDOW_H
