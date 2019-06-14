#include "AbstractTool.h"

AbstractTool::AbstractTool(const QString& name) : m_name(name) {
}

AbstractTool::~AbstractTool() {
}

QString AbstractTool::name() const {
  return m_name;
}

bool AbstractTool::isUsing() const {
  return m_isUsing;
}

bool AbstractTool::isSelectable() const {
  return m_isNodeSelectable;
}
