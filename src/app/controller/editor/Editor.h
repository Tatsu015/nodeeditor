#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>
#include <QList>

class Project;
class AbstractAction;
class QGraphicsView;
class AbstractTool;
class QUndoStack;
class QUndoCommand;

class Editor : public QObject{
  Q_OBJECT

 public:
  static Editor* getInstance();

  void init();
  void reset();

  Project* project() const;

  void setGraphicsView(QGraphicsView* graphicsView);

  AbstractTool* tool(const QString& toolName) const;
  AbstractTool* activeTool() const;
  void changeActiveTool(const QString& toolName);
  void changeDefaultTool();
  void addCommand(QUndoCommand* undoCommand);

  QUndoStack* undoStack() const;

signals:
  void projectNameChanged(QString& projectName);

 private:
  void initFactory();
  void initTool();
  void initUndoStack();
  void resetProject();
  void addTool(AbstractTool* tool);

 private:
  //  QList<AbstractAction*> m_actions;
  QMap<QString, AbstractTool*> m_tools;
  AbstractTool* m_activeTool = nullptr;
  Project* m_project = nullptr;
  QGraphicsView* m_graphicsView = nullptr;
  QUndoStack* m_undoStack = nullptr;

 private:
  Editor(QObject *parent=nullptr);
  ~Editor();
};

#endif  // EDITOR_H
