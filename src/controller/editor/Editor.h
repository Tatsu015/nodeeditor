#ifndef EDITOR_H
#define EDITOR_H

#include <QList>

class Project;
class AbstractAction;
class QGraphicsView;


class Editor
{
public:
    static Editor* getInstance();

    void init();
    AbstractAction* action(const QString &name);
    void addAction(AbstractAction* action);


    Project *project() const;

    void setGraphicsView(QGraphicsView *graphicsView);

private:
    QList<AbstractAction*> m_actions;
    Project* m_project            = nullptr;
    QGraphicsView* m_graphicsView = nullptr;

private:
    Editor();
    ~Editor();
};


#endif // EDITOR_H
