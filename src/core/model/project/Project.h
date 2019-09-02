#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QString>

class Scene;
class Sheet;
class ProjectObserver;

class Project {
public:
  Project();
  ~Project();

  void run();
  void reset();

  bool open(const QString& filePath);
  bool save(const QString& filePath);

  QString filePath() const;
  QString fileBaseName() const;

  QList<Sheet*> sheets() const;
  Sheet* sheet(const QString& sheetName) const;
  void addSheet(Sheet* sheet);
  void removeSheet(Sheet* sheet);
  void removeSheet(const QString& sheetName);

  Sheet* activeSheet() const;
  void setActiveSheet(Sheet* activeSheet);
  void setActiveSheet(const QString& sheetName);
  void changeActiveSheet(const int32_t index);
  void changeActiveSheet(const QString& sheetName);

  void addObserver(ProjectObserver* projectObserver);

  Scene* scene() const;

  bool nodeNameVisible() const;
  void setNodeNameVisible(bool nodeNameVisible);
  void takeOver(Project* project);

private:
  QByteArray toJson();
  void fromJson(const QByteArray& data);
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
