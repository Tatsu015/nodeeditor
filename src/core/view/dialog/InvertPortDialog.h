#ifndef INVERTPORTDIALOG_H
#define INVERTPORTDIALOG_H

#include <QDialog>
#include <QMap>

class QCheckBox;
class QGridLayout;
class AbstractNode;
class Port;

namespace Ui {
class InvertPortDialog;
}

class InvertPortDialog : public QDialog {
  Q_OBJECT

public:
  explicit InvertPortDialog(QWidget* parent = nullptr);
  virtual ~InvertPortDialog();

  void setupDialog(const AbstractNode* node);
  QList<Port*> invertPorts() const;

private:
  Ui::InvertPortDialog* ui = nullptr;
  QGridLayout* m_checkboxLayout = nullptr;
  QMap<QCheckBox*, Port*> m_namePortMaps;
};

#endif // INVERTPORTDIALOG_H
