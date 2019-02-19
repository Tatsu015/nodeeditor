#ifndef FORDEBUGCONTROLWIDGET_H
#define FORDEBUGCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class DebugControlWidget;
}

class DebugControlWidget : public QWidget
{
  Q_OBJECT

public:
  explicit DebugControlWidget(QWidget *parent = 0);
  virtual ~DebugControlWidget();

  Ui::DebugControlWidget* ui() const;

  void setup();
  void tearDown();

private:
  Ui::DebugControlWidget *m_ui;
};

#endif // FORDEBUGCONTROLWIDGET_H
