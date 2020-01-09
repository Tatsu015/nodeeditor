#ifndef CONNECTTOPORTCOMMAND_H
#define CONNECTTOPORTCOMMAND_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Sheet;
class AbstractConnection;
class Port;
class Connector;

class ConnectToPortCommand : public QUndoCommand {
public:
  ConnectToPortCommand(Scene* scene, Sheet* sheet, AbstractConnection* connection, Port* startPort, Port* endPort,
                       QList<QPointF> vertexes);
  virtual ~ConnectToPortCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  AbstractConnection* m_connection = nullptr;
  Port* m_startPort = nullptr;
  Port* m_endPort = nullptr;
  QList<QPointF> m_vertexes;
};

#endif // CONNECTTOPORTCOMMAND_H
