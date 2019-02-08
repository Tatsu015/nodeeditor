#ifndef PROJECT_H
#define PROJECT_H

#include <QString>

class Scene;

class Project {
 public:
  Project();
  ~Project();

  void init();

  bool open(const QString& filePath);

  bool save(const QString& filePath);

  QString filePath() const;

  Scene* scene() const;

 private:
  QByteArray toJson();
  void fromJson(const QByteArray& data);

 private:
  Scene* m_scene = nullptr;
  QString m_filePath;
};

#endif  // PROJECT_H
