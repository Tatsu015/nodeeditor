#ifndef PROJECTOBSERVER_H
#define PROJECTOBSERVER_H

class Sheet;

class ProjectObserver {
public:
  ProjectObserver();
  virtual ~ProjectObserver();

  virtual void addSheet(Sheet* sheet) = 0;
  virtual void changeSheet(Sheet* sheet) = 0;
  virtual void removeSheet(Sheet* sheet) = 0;
};

#endif // PROJECTOBSERVER_H
