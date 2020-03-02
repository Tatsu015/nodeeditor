#include "OpenPlugin.h"
#include "Editor.h"
#include "MenuManager.h"
#include "PluginLoader.h"
#include "Project.h"
#include "ProjectParser.h"
#include <QFileDialog>
#include <QJsonDocument>
#include <QMenu>

OpenPlugin::OpenPlugin(QObject* parent) : AbstractPlugin(parent) {
}

OpenPlugin::~OpenPlugin() {
}

void OpenPlugin::doInit() {
  QMenu* menu = MenuManager::getInstance()->menu(MenuManager::MENU_FILE);

  QAction* openAction = new QAction(QIcon("../resource/open.png"), "Open");
  openAction->setShortcut(QKeySequence::Open);
  menu->addAction(openAction);

  connect(openAction, &QAction::triggered, this, &OpenPlugin::onExecute);
}

void OpenPlugin::onExecute() {
  Project* lastProject = Editor::getInstance()->project();

  QString filePath = QFileDialog::getOpenFileName(nullptr, "Open file", ".", "*.nd");

  QFile f(filePath);
  if (!f.open(QIODevice::ReadOnly)) {
    return;
  }

  ProjectParser parser;
  QByteArray data = f.readAll();
  Project* newProject = parser.parse(data, lastProject);

  delete lastProject;
  newProject->setFilePath(filePath);
  Editor::getInstance()->changeProject(newProject);
  PluginLoader::getInstance()->reset();

  newProject->setActiveSheet(newProject->sheets().first());
  newProject->changeActiveSheet(0);
}
