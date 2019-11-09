#include "SheetListWidget.h"
#include "Editor.h"
#include "Project.h"
#include "Sheet.h"
#include "SheetChangeHistoryStack.h"
#include "SheetFactory.h"
#include "ui_SheetListWidget.h"
#include <QDebug>
#include <QDir>
#include <QInputDialog>
#include <QMenu>

SheetListWidget::SheetListWidget(QWidget* parent) : QWidget(parent), ui(new Ui::SheetListWidget) {
  ui->setupUi(this);

  ui->findLineEdit->setDisabled(true);

  ui->sheetListWidget->setContextMenuPolicy(Qt::CustomContextMenu);

  m_addSheetNameAction = new QAction("Add");
  connect(m_addSheetNameAction, &QAction::triggered, this, &SheetListWidget::onAddSheext);
  m_deleteSheetNameAction = new QAction("Delete");
  connect(m_deleteSheetNameAction, &QAction::triggered, this, &SheetListWidget::onDeleteSheet);
  m_renameSheetAction = new QAction("Rename");
  connect(m_renameSheetAction, &QAction::triggered, this, &SheetListWidget::onChangeSheetName);

  connect(ui->addPushButton, &QPushButton::clicked, this, &SheetListWidget::onAddSheext);
  connect(ui->deletePushButton, &QPushButton::clicked, this, &SheetListWidget::onDeleteSheet);
  connect(ui->sheetListWidget, &QListWidget::itemDoubleClicked, this, &SheetListWidget::onChangeActiveSheet);

  connect(ui->sheetListWidget, &QListWidget::customContextMenuRequested, this, &SheetListWidget::onExecContextMenu);
}

SheetListWidget::~SheetListWidget() {
  delete ui;
}

void SheetListWidget::addSheet(Sheet* sheet) {
  QListWidgetItem* item = new QListWidgetItem(sheet->name());
  ui->sheetListWidget->addItem(item);
}

void SheetListWidget::changeSheet(Sheet* sheet) {
  QList<QListWidgetItem*> items = ui->sheetListWidget->findItems(sheet->name(), Qt::MatchExactly);
  if (0 >= items.count()) {
    return;
  }
  QListWidgetItem* item = items.first();
  ui->sheetListWidget->setCurrentItem(item);
}

void SheetListWidget::removeSheet(Sheet* sheet) {
  QList<QListWidgetItem*> items = ui->sheetListWidget->findItems(sheet->name(), Qt::MatchExactly);
  if (0 >= items.count()) {
    return;
  }
  QListWidgetItem* item = items.first();
  ui->sheetListWidget->removeItemWidget(item);
  delete item;
}

void SheetListWidget::onAddSheext() {
  Project* project = Editor::getInstance()->project();
  Sheet* sheet = SheetFactory::getInstance()->createSheet(project->sheetNames());
  project->addSheet(sheet);
  project->setActiveSheet(sheet);
  SheetChangeHistoryController::getInstance()->add(sheet->name());
}

void SheetListWidget::onDeleteSheet() {
  QListWidgetItem* item = ui->sheetListWidget->currentItem();
  if (!item) {
    return;
  }
  QString sheetName = ui->sheetListWidget->currentItem()->text();
  Project* project = Editor::getInstance()->project();
  project->removeSheet(sheetName);
}

void SheetListWidget::onChangeSheetName() {
  QListWidgetItem* item = ui->sheetListWidget->currentItem();
  if (!item) {
    return;
  }

  Project* project = Editor::getInstance()->project();
  bool ok;
  QString newSheetName =
      QInputDialog::getText(this, tr("Rename"), tr("New sheet name"), QLineEdit::Normal, item->text(), &ok);

  if (ok && !newSheetName.isEmpty()) {
    Sheet* sheet = project->sheet(item->text());
    sheet->setName(newSheetName);
    item->setText(newSheetName);
  }
}

void SheetListWidget::onChangeActiveSheet(QListWidgetItem* item) {
  Project* project = Editor::getInstance()->project();
  QString name = item->text();
  project->changeActiveSheet(name);
  SheetChangeHistoryController::getInstance()->add(name);
}

void SheetListWidget::onExecContextMenu(const QPoint& pos) {
  QListWidgetItem* item = ui->sheetListWidget->itemAt(pos);
  QPoint globalPos = ui->sheetListWidget->mapToGlobal(pos);

  QMenu contextMenu;
  if (item) {
    contextMenu.addAction(m_addSheetNameAction);
    contextMenu.addAction(m_deleteSheetNameAction);
    contextMenu.addAction(m_renameSheetAction);
    contextMenu.exec(globalPos);
  } else {
    contextMenu.addAction(m_addSheetNameAction);
    contextMenu.exec(globalPos);
  }
}
