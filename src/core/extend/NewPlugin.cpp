#include "NewPlugin.h"
#include "Editor.h"
#include "MenuManager.h"
#include "PluginLoader.h"
#include "Project.h"
#include "SheetFactory.h"
#include <QFileDialog>
#include <QMenu>

NewPlugin::NewPlugin(QObject* parent) : AbstractPlugin(parent) {
}

NewPlugin::~NewPlugin() {
}

void NewPlugin::doInit() {
  QMenu* menu = MenuManager::getInstance()->menu(MenuManager::MENU_FILE);

  QAction* newAction = new QAction(QIcon("../resource/new.png"), "New");
  newAction->setShortcut(QKeySequence::New);
  menu->addAction(newAction);

  connect(newAction, &QAction::triggered, this, &NewPlugin::onExecute);
}

void NewPlugin::onExecute() {
  Project* oldProject = Editor::getInstance()->project();
  Project* newProject = new Project();

  newProject->takeOver(oldProject);
  delete oldProject;
  QUuid uuid = QUuid::createUuid();
  Sheet* sheet = SheetFactory::getInstance()->createSheet(uuid.toString(), uuid.toString());
  newProject->addSheet(sheet);
  newProject->setActiveSheet(sheet);
  Editor::getInstance()->changeProject(newProject);
  Editor::getInstance()->run();
  PluginLoader::getInstance()->reset();
}
