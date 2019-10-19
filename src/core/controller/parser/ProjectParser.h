#ifndef PROJECTPARSER_H
#define PROJECTPARSER_H

#include <QByteArray>
#include <QJsonObject>

class Project;
class Sheet;
class AbstractNode;
class Connection;

class ProjectParser {
public:
  ProjectParser();
  ~ProjectParser();

  Project* parse(const QByteArray& data);

private:
  Sheet* parseSheet(QJsonValue sheetJsonVal);
  AbstractNode* parseNode(QJsonValue nodeJsonVal);
  Connection* parseNodeToNodeConnection(const Sheet* sheet, QJsonValue connectionJsonVal);
  Connection* parseNodeToConnectorConnection(const Sheet* sheet, QJsonValue connectionJsonVal);
};

#endif // PROJECTPARSER_H
