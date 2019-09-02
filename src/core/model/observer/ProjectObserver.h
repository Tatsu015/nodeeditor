#ifndef ProjectObserver_H
#define ProjectObserver_H

class Sheet;

class ProjectObserver {
public:
  ProjectObserver();
  virtual ~ProjectObserver();

  virtual void addSheet(Sheet* sheet) = 0;
  virtual void removeSheet(Sheet* sheet) = 0;
};

#endif // ProjectObserver_H
