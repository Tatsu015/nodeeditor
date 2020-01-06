#ifndef FUNCTIONBLOCKTOOLBUTTON_H
#define FUNCTIONBLOCKTOOLBUTTON_H

#include "ProjectObserver.h"
#include <QToolButton>

class FunctionBlockToolButton : public QToolButton, public ProjectObserver {
  Q_OBJECT

public:
  FunctionBlockToolButton(QWidget* parent = nullptr);
  virtual ~FunctionBlockToolButton();

  virtual void addSheet(Sheet* sheet);
  virtual void changeSheet(Sheet* sheet);
  virtual void removeSheet(Sheet* sheet);

  bool hasAction() const;

private slots:
  void onChangeFunctionBlock();
  void onChangeNodeType();

private:
  QMenu* m_menu = nullptr;
};

#endif // FUNCTIONBLOCKTOOLBUTTON_H
