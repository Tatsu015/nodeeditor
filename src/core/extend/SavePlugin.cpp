#include "SavePlugin.h"
#include "Editor.h"
#include "MenuManager.h"
#include "Project.h"
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMenu>
#include <QMessageBox>

SavePlugin::SavePlugin(QObject* parent) : AbstractPlugin(parent) {
}

SavePlugin::~SavePlugin() {
}

void SavePlugin::doInit() {
  QMenu* menu = MenuManager::getInstance()->menu(MenuManager::MENU_FILE);

  QAction* saveAction = new QAction(QIcon("../resource/save.png"), "Save");
  saveAction->setShortcut(QKeySequence::Save);
  menu->addAction(saveAction);

  connect(saveAction, &QAction::triggered, this, &SavePlugin::onExecuteSave);

  QAction* saveAsAction = new QAction(QIcon("../resource/save.png"), "Save As");
  saveAsAction->setShortcut(QKeySequence::SaveAs);
  menu->addAction(saveAsAction);

  connect(saveAsAction, &QAction::triggered, this, &SavePlugin::onExecuteSaveAs);
}

void SavePlugin::save(const QString& filePath) {
  QFile f(filePath);
  if (!f.open(QIODevice::WriteOnly)) {
    QMessageBox::warning(nullptr, "Warning", "Can not create " + filePath);
    return;
  }

  Project* project = Editor::getInstance()->project();
  project->setFilePath(filePath);

  QJsonObject jsonObj = project->toJson();
  QJsonDocument doc(jsonObj);

  f.write(doc.toJson());
  f.close();

  Editor::getInstance()->projectNameChanged(project->fileBaseName());
}

void SavePlugin::onExecuteSave() {
  Project* project = Editor::getInstance()->project();
  QString filePath = project->filePath();

  //  project->save(fileName);

  save(filePath);
}

void SavePlugin::onExecuteSaveAs() {
  QString filePath = QFileDialog::getSaveFileName(nullptr);

  if (filePath.isEmpty()) {
    return;
  }

  save(filePath);
}
