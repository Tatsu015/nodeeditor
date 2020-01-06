#ifndef TOOLBUTTONGROUP_H
#define TOOLBUTTONGROUP_H

#include <QObject>
#include <QToolButton>

class ToolButtonGroup : public QObject {
  Q_OBJECT
public:
  explicit ToolButtonGroup(QObject* parent = nullptr);
  virtual ~ToolButtonGroup();

  void add(QToolButton* toolButton);
  QList<QToolButton*> toolButtons() const;
  void activateDefault();

private slots:
  void onExclusiveButtonPress();

private:
  QList<QToolButton*> m_toolButtons;
};

#endif // TOOLBUTTONGROUP_H
