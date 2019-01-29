#ifndef EDITOR_H
#define EDITOR_H

#include <QList>
#include "Scene.h"

class Scene;
class AbstractAction;

class Editor
{
public:
    Editor();
    ~Editor();

    AbstractAction* action(QString& name);

    Scene *scene() const;

private:
    QList<AbstractAction*> m_actions;
    Scene* m_scene = nullptr;
};

#endif // EDITOR_H
