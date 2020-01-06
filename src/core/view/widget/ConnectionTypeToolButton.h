#ifndef CONNECTIONTYPETOOLBUTTON_H
#define CONNECTIONTYPETOOLBUTTON_H

#include <QToolButton>

class ConnectionCreateTool;

class ConnectionTypeToolButton : public QToolButton {
  Q_OBJECT
public:
  ConnectionTypeToolButton(QWidget* parent = nullptr);
  virtual ~ConnectionTypeToolButton();
  void setup();

public slots:
  void onChangeConnetionType();
};

#endif // CONNECTIONTYPETOOLBUTTON_H
