#include "TmpConnection.h"
#include <QPen>
#include "Connector.h"
#include "Define.h"
#include "Port.h"

const QColor TmpConnection::CREATING_LINE_COLOR = QColor("#AA8888");
const QColor TmpConnection::DECIDED_LINE_COLOR = QColor("#FFFFFF");

TmpConnection::TmpConnection(QGraphicsItem* parent) : Connection(parent) { setPen(QPen(CREATING_LINE_COLOR, PEN_SIZE, Qt::DotLine)); }

TmpConnection::~TmpConnection() {}

TmpConnection* TmpConnection::create() { return new TmpConnection(); }

void TmpConnection::changePenStyle(const bool connectable) {
  if (connectable) {
    setPen(QPen(DECIDED_LINE_COLOR, PEN_SIZE, Qt::SolidLine));
  } else {
    setPen(QPen(CREATING_LINE_COLOR, PEN_SIZE, Qt::DotLine));
  }
}
