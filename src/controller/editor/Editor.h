#ifndef EDITOR_H
#define EDITOR_H

#include <QList>

class Scene;
class AbstractAction;


class Editor
{
public:
    static Editor* getInstance();

    AbstractAction* action(const QString &name);
    void addAction(AbstractAction* action);

    Scene *scene() const;

private:
    QList<AbstractAction*> m_actions;
    Scene* m_scene = nullptr;

private:
    Editor();
    ~Editor();
};


#endif // EDITOR_H
