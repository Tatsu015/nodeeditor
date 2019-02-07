#include "AbstractTool.h"

AbstractTool::AbstractTool(const QString &name) {}

AbstractTool::~AbstractTool() {}

QString AbstractTool::name() { return m_name; }

bool AbstractTool::isUsing() { return m_isUsing; }
