#include "FunctionBlockNode.h"
#include "Define.h"
#include "Port.h"
#include "Sheet.h"
#include <QBrush>
#include <QPen>

FunctionBlockNode::FunctionBlockNode(Sheet* sheet, QGraphicsItem* parent) : AbstractNode(parent) {
  m_sheet = sheet;
  m_nodeType = sheet->name();

  m_io = Undefined;

  QPainterPath path;
  path.addRoundedRect(0, 0, WIDTH, HEIGHT, ROUND_RADIUS, ROUND_RADIUS);
  setPath(path);
}

FunctionBlockNode::~FunctionBlockNode() {
}

AbstractNode* FunctionBlockNode::create(const QString& id) {
  FunctionBlockNode* node = new FunctionBlockNode(m_sheet);
  node->m_id = id;
  return node;
}

bool FunctionBlockNode::execute(QList<bool> args) {
  return args.at(0);
}

void FunctionBlockNode::doSetup() {

  int32_t inNodeCount = m_sheet->inNodeCount();
  int32_t outNodeCount = m_sheet->outNodeCount();

  int32_t largerNodeCount = qMax(inNodeCount, outNodeCount);
  if (4 < largerNodeCount) {
    int32_t step = 1 + largerNodeCount / 4;
    QPainterPath path;
    path.addRoundedRect(0, 0, WIDTH, HEIGHT * step, ROUND_RADIUS, ROUND_RADIUS);
    setPath(path);
  }

  int32_t portNum = 1;
  for (int32_t i = 0; i < inNodeCount; ++i) {
    addInputPort(new Port(Input, portNum, this, false, false));
    ++portNum;
  }
  for (int32_t i = 0; i < outNodeCount; ++i) {
    addOutputPort(new Port(Output, portNum, this, false, false));
  }
}
