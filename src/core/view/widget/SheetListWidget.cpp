#include "SheetListWidget.h"
#include "Editor.h"
#include "Project.h"
#include "Sheet.h"
#include "SheetFactory.h"
#include "ui_SheetListWidget.h"

SheetListWidget::SheetListWidget(QWidget* parent) : QWidget(parent), ui(new Ui::SheetListWidget) {
  ui->setupUi(this);
  connect(ui->addPushButton, &QPushButton::clicked, this, &SheetListWidget::onAddSheext);
  connect(ui->deletePushButton, &QPushButton::clicked, this, &SheetListWidget::onDeleteSheet);
  connect(ui->sheetListWidget, &QListWidget::itemDoubleClicked, this, &SheetListWidget::onChangeActiveSheet);
}

SheetListWidget::~SheetListWidget() {
  delete ui;
}

void SheetListWidget::addSheet(Sheet* sheet) {
  ui->sheetListWidget->addItem(sheet->name());
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
  Sheet* sheet = SheetFactory::getInstance()->createSheet();
  project->addSheet(sheet);
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

void SheetListWidget::onChangeActiveSheet(QListWidgetItem* item) {
  Project* project = Editor::getInstance()->project();
  project->changeActiveSheet(item->text());
}
