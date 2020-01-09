#ifndef SHEETLISTWIDGET_H
#define SHEETLISTWIDGET_H

#include "ProjectObserver.h"
#include <QListWidgetItem>

class QWidget;

namespace Ui {
class SheetListWidget;
}

class SheetListWidget : public QWidget, public ProjectObserver {
  Q_OBJECT

public:
  explicit SheetListWidget(QWidget* parent = 0);
  ~SheetListWidget();

  virtual void addSheet(Sheet* sheet);
  virtual void changeSheet(Sheet* sheet);
  virtual void removeSheet(Sheet* sheet);

private slots:
  void onAddSheext();
  void onDeleteSheet();
  void onChangeSheetName();
  //  void onChangeSheetName(QListWidgetItem* item);
  void onChangeActiveSheet(QListWidgetItem* item);
  void onExecContextMenu(const QPoint& pos);

private:
  Ui::SheetListWidget* ui = nullptr;
  QAction* m_addSheetNameAction = nullptr;
  QAction* m_deleteSheetNameAction = nullptr;
  QAction* m_renameSheetAction = nullptr;
};

#endif // SHEETLISTWIDGET_H
