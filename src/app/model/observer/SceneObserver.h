#ifndef SCENEOBSERVER_H
#define SCENEOBSERVER_H

class AbstractNode;

class SceneObserver {
 public:
  SceneObserver();
  virtual ~SceneObserver();

  virtual void addNode(AbstractNode* node) = 0;
  virtual void removeNode(AbstractNode* node) = 0;
};

#endif  // SCENEOBSERVER_H
