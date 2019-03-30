#ifndef TMPTmpConnection_H
#define TMPTmpConnection_H

#include "Connection.h"

class Port;
class Connector;

class TmpConnection : public Connection {
public:
    enum PenStyle : uint32_t{
        Connected,
        Connecting,
    };

 public:
  TmpConnection(QGraphicsItem* parent = nullptr);
  virtual ~TmpConnection();

  virtual TmpConnection* create();

  void changePenStyle(const PenStyle style);

 private:
  const static QColor CREATING_LINE_COLOR;
  const static QColor DECIDED_LINE_COLOR;
};

#endif  // TMPTmpConnection_H
