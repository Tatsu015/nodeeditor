#ifndef PROJECTPARSER_H
#define PROJECTPARSER_H

#include <QByteArray>
#include <QJsonObject>

class Project;
class Sheet;
class AbstractNode;
class AbstractConnection;

class ProjectParser {
public:
  ProjectParser();
  ~ProjectParser();

  Project* parse(const QByteArray& data, Project* lastProject);

private:
  Sheet* parseSheet(QJsonValue sheetJsonVal);
  AbstractNode* parseNode(QJsonValue nodeJsonVal);
  AbstractConnection* parseNodeToNodeConnection(const Sheet* sheet, QJsonValue connectionJsonVal);
  AbstractConnection* parseNodeToConnectorConnection(const Sheet* sheet, QJsonValue connectionJsonVal);
};

#endif // PROJECTPARSER_H
