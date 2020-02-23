#include "PortAddCommand.h"
#include "AbstractNode.h"
#include "Port.h"
#include "Scene.h"
#include "Sheet.h"

PortAddCommand::PortAddCommand(Scene* scene, Sheet* sheet, AbstractNode* node, Port* port)
    : QUndoCommand(), m_scene(scene), m_sheet(sheet), m_node(node), m_port(port) {
}

PortAddCommand::~PortAddCommand() {
}

void PortAddCommand::redo() {
  m_scene->changeSheet(m_sheet);
  m_node->addInputPort(m_port);
  m_port->setParentItem(m_node);
  m_node->redraw();
}

void PortAddCommand::undo() {
  m_node->removePort(m_port);
  m_scene->removeItem(m_port);
  m_node->redraw();
}
