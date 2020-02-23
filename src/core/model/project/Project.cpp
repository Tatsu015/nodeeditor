#include "Project.h"
#include "AbstractNode.h"
#include "Connector.h"
#include "Editor.h"
#include "Port.h"
#include "PortFactory.h"
#include "ProjectKeyDefine.h"
#include "ProjectObserver.h"
#include "Scene.h"
#include "Sheet.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

const static QString DEFAULT_FILE_NAME = "Undefined." + APP_EXTENSION;

Project::Project() {
  QDir dir;
  m_filePath = dir.absolutePath() + "/" + DEFAULT_FILE_NAME;
  m_scene = new Scene();
}

Project::~Project() {
  foreach (Sheet* sheet, m_sheets) { removeSheet(sheet); }
  qDeleteAll(m_sheets);
  delete m_scene;
}

void Project::reset() {
  foreach (Sheet* sheet, m_sheets) { removeSheet(sheet); }
  m_activeSheet = nullptr;
}

QJsonObject Project::toJson() {
  QJsonArray sheetJsonArray;

  foreach (Sheet* sheet, m_sheets) { sheetJsonArray.append(sheet->toJsonObj()); }

  QJsonObject jsonObj;
  jsonObj[JSON_NODE_NAME_VISIBLE] = m_nodeNameVisible;
  jsonObj[JSON_NODE_NAME_VISIBLE] = m_nodeIdVisible;
  jsonObj[JSON_SHEETS] = sheetJsonArray;

  return jsonObj;
}

QString Project::filePath() const {
  return m_filePath;
}

void Project::setFilePath(const QString& filePath) {
  m_filePath = filePath;
}

QString Project::fileBaseName() const {
  QFileInfo info(m_filePath);
  return info.baseName();
}

QList<Sheet*> Project::sheets() const {
  return m_sheets;
}

Sheet* Project::sheet(const QString& sheetName) const {
  foreach (Sheet* sheet, m_sheets) {
    if (sheetName == sheet->name()) {
      return sheet;
    }
  }
  return nullptr;
}

void Project::addSheet(Sheet* sheet) {
  m_sheets << sheet;
  foreach (ProjectObserver* projectObserver, m_projectObservers) { projectObserver->addSheet(sheet); }
}

void Project::removeSheet(Sheet* sheet) {
  int32_t index = m_sheets.indexOf(sheet);
  m_sheets.removeOne(sheet);
  m_scene->removeSheet();
  foreach (ProjectObserver* projectObserver, m_projectObservers) { projectObserver->removeSheet(sheet); }

  if (0 == sheetCount()) {
    return;
  }

  // set next sheet index
  int32_t nextIndex = index;
  if (0 >= index) {
    nextIndex = 0;
  } else if (index < sheetCount()) {
    nextIndex = index;
  } else {
    nextIndex = index - 1;
  }
  changeActiveSheet(nextIndex);
}

void Project::removeSheet(const QString& sheetName) {
  Sheet* willRemoveSheet = sheet(sheetName);
  if (willRemoveSheet) {
    removeSheet(willRemoveSheet);
  }
}

int32_t Project::sheetCount() const {
  return m_sheets.count();
}

QStringList Project::sheetNames() const {
  QStringList names;
  foreach (Sheet* sheet, m_sheets) { names << sheet->name(); }
  return names;
}

Sheet* Project::activeSheet() const {
  return m_activeSheet;
}

void Project::setActiveSheet(Sheet* activeSheet) {
  m_activeSheet = activeSheet;
  foreach (ProjectObserver* projectObserver, m_projectObservers) { projectObserver->changeSheet(m_activeSheet); }
  m_scene->setSheet(m_activeSheet);
}

void Project::setActiveSheet(const QString& sheetName) {
  Sheet* willActiveSheet = sheet(sheetName);
  if (willActiveSheet) {
    setActiveSheet(willActiveSheet);
  }
}

void Project::changeActiveSheet(const int32_t index) {
  Sheet* willActiveSheet = m_sheets.at(index);
  if (willActiveSheet) {
    changeActiveSheet(willActiveSheet->name());
  }
}

void Project::changeActiveSheet(const QString& sheetName) {
  m_activeSheet = sheet(sheetName);
  m_scene->changeSheet(m_activeSheet);
  foreach (ProjectObserver* projectObserver, m_projectObservers) { projectObserver->changeSheet(m_activeSheet); }
  // need to update because when after
  // change sheet, graphics trash
  // remain...
  m_scene->update();
}

void Project::addObserver(ProjectObserver* projectObserver) {
  m_projectObservers << projectObserver;
}

bool Project::nodeNameVisible() const {
  return m_nodeNameVisible;
}

void Project::setNodeNameVisible(bool visible) {
  m_nodeNameVisible = visible;
}

bool Project::nodeIdVisible() const {
  return m_nodeIdVisible;
}

void Project::setNodeIdVisible(bool visible) {
  m_nodeIdVisible = visible;
}

void Project::takeOver(Project* src) {
  m_projectObservers = src->m_projectObservers;
  m_nodeNameVisible = src->m_nodeNameVisible;
  m_nodeIdVisible = src->m_nodeIdVisible;
}

Scene* Project::scene() const {
  return m_scene;
}
