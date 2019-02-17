#include "DebugControlDialog.h"
#include "ui_DebugControlDialog.h"

DebugControlDialog::DebugControlDialog(QWidget *parent) :
  QWidget(parent),
  m_ui(new Ui::DebugControlDialog)
{
  m_ui->setupUi(this);
}

DebugControlDialog::~DebugControlDialog()
{
  delete m_ui;
}

Ui::DebugControlDialog* DebugControlDialog::ui() const
{
  return m_ui;
}
