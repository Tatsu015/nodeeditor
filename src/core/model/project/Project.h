#ifndef PROJECT_H
#define PROJECT_H

#include <QJsonObject>
#include <QList>
#include <QString>

class Scene;
class Sheet;
class ProjectObserver;
class AbstractNode;

const static QString APP_EXTENSION = "nd";

class Project {
public:
  Project();
  ~Project();

  void reset();

  QJsonObject toJson();

  QString filePath() const;
  void setFilePath(const QString& filePath);
  QString fileBaseName() const;

  QList<Sheet*> sheets() const;
  Sheet* sheet(const QString& sheetName) const;
  void addSheet(Sheet* sheet);
  void removeSheet(Sheet* sheet);
  void removeSheet(const QString& sheetName);
  int32_t sheetCount() const;
  QStringList sheetNames() const;

  Sheet* activeSheet() const;
  void setActiveSheet(Sheet* activeSheet);
  void setActiveSheet(const QString& sheetName);
  void changeActiveSheet(const int32_t index);
  void changeActiveSheet(const QString& sheetName);

  void addObserver(ProjectObserver* projectObserver);

  Scene* scene() const;

  bool nodeNameVisible() const;
  void setNodeNameVisible(bool nodeNameVisible);
  void takeOver(Project* src);

private:
  void notify();

private:
  Scene* m_scene = nullptr;
  QString m_filePath;
  bool m_nodeNameVisible = true;
  QList<ProjectObserver*> m_projectObservers;
  QList<Sheet*> m_sheets;
  Sheet* m_activeSheet = nullptr;
};

#endif // PROJECT_H
