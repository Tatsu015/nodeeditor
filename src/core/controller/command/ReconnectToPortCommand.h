#ifndef RECONNECTTOPORTCOMMAND_H
#define RECONNECTTOPORTCOMMAND_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Sheet;
class AbstractConnection;
class Port;
class Connector;

class ReconnectToPortCommand : public QUndoCommand {
public:
  ReconnectToPortCommand(Scene* scene, Sheet* sheet, AbstractConnection* connection, Port* lastPort, Port* targetPort,
                         bool isMoveStartPort);
  virtual ~ReconnectToPortCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  AbstractConnection* m_connection = nullptr;
  Port* m_lastPort = nullptr;
  Port* m_targetPort = nullptr;
  bool m_isMoveStartPort = false;
};

#endif // RECONNECTTOPORTCOMMAND_H
