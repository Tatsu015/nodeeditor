#ifndef ReReconnectToPortCommand_H
#define ReReconnectToPortCommand_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Sheet;
class Connection;
class Port;
class Connector;

class ReconnectToPortCommand : public QUndoCommand {
public:
  ReconnectToPortCommand(Scene* scene, Sheet* sheet, Connection* connection, Port* lastPort, Port* targetPort,
                         bool isMoveStartPort);
  virtual ~ReconnectToPortCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  Connection* m_connection = nullptr;
  Port* m_lastPort = nullptr;
  Port* m_targetPort = nullptr;
  bool m_isMoveStartPort = false;
};

#endif // ReReconnectToPortCommand_H
