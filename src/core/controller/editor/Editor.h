#ifndef EDITOR_H
#define EDITOR_H

#include <QList>
#include <QObject>

class Project;
class AbstractAction;
class QGraphicsView;
class AbstractTool;
class QUndoStack;
class QUndoCommand;

class Editor : public QObject {
  Q_OBJECT

public:
  static Editor* getInstance();

  void init();
  void run();

  Project* project() const;
  void changeProject(Project* project);

  void setGraphicsView(QGraphicsView* graphicsView);

  AbstractTool* tool(const QString& toolName) const;
  AbstractTool* activeTool() const;
  void changeActiveTool(const QString& toolName);
  void changeDefaultTool();
  void addCommand(QUndoCommand* undoCommand);

  QUndoStack* undoStack() const;

signals:
  void projectNameChanged(const QString& projectName);

private:
  void initFactory();
  void initTool();
  void initUndoStack();
  void addTool(AbstractTool* tool);

private:
  QMap<QString, AbstractTool*> m_tools;
  AbstractTool* m_activeTool = nullptr;
  Project* m_project = nullptr;
  QGraphicsView* m_graphicsView = nullptr;
  QUndoStack* m_undoStack = nullptr;

private:
  Editor(QObject* parent = nullptr);
  ~Editor();
};

#endif // EDITOR_H
