#include "TmpConnection.h"
#include "Connector.h"
#include "Define.h"
#include "Port.h"
#include <QPen>

const QColor TmpConnection::CREATING_LINE_COLOR = QColor("#AA8888");
const QColor TmpConnection::DECIDED_LINE_COLOR = QColor("#FFFFFF");

TmpConnection::TmpConnection(QGraphicsItem* parent) : Connection(parent) {
  setPen(QPen(CREATING_LINE_COLOR, PEN_SIZE, Qt::DotLine));
}

TmpConnection::~TmpConnection() {
}

Connection* TmpConnection::create() {
  return create("0");
}

Connection* TmpConnection::create(const QString& id) {
  Q_UNUSED(id);
  TmpConnection* connection = new TmpConnection();
  return connection;
}

void TmpConnection::changePenStyle(const PenStyle style) {
  if (Connecting == style) {
    setPen(QPen(CREATING_LINE_COLOR, PEN_SIZE, Qt::DotLine));
  } else {
    setPen(QPen(DECIDED_LINE_COLOR, PEN_SIZE, Qt::SolidLine));
  }
}
