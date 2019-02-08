#ifndef EDITOR_H
#define EDITOR_H

#include <QList>

class Project;
class AbstractAction;
class QGraphicsView;
class AbstractTool;

class Editor {
 public:
  static Editor* getInstance();

  void init();
  void reset();
  AbstractAction* action(const QString& name);
  void addAction(AbstractAction* action);

  Project* project() const;

  void setGraphicsView(QGraphicsView* graphicsView);

  AbstractTool* tool(const QString& toolName) const;
  AbstractTool* activeTool() const;
  void changeActiveTool(const QString& toolName);
  void changeDefaultTool();

 private:
  void initFactory();
  void intAction();
  void initTool();
  void resetProject();
  void addTool(AbstractTool* tool);

 private:
  //  QList<AbstractAction*> m_actions;
  QMap<QString, AbstractTool*> m_tools;
  AbstractTool* m_activeTool = nullptr;
  Project* m_project = nullptr;
  QGraphicsView* m_graphicsView = nullptr;

 private:
  Editor();
  ~Editor();
};

#endif  // EDITOR_H
