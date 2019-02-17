#ifndef DEBUGCONTROLDIALOG_H
#define DEBUGCONTROLDIALOG_H

#include <QWidget>

namespace Ui {
class DebugControlDialog;
}

class DebugControlDialog : public QWidget
{
  Q_OBJECT

public:
  explicit DebugControlDialog(QWidget *parent = 0);
  ~DebugControlDialog();

  // do not so gooooood system setting
  Ui::DebugControlDialog* ui() const;

private:
  Ui::DebugControlDialog *m_ui = nullptr;
};

#endif // DEBUGCONTROLDIALOG_H
