#ifndef ERRORLISTWIDGET_H
#define ERRORLISTWIDGET_H

#include <QListWidget>
#include "Common.h"

class QWidget;
class AnalyzeCircuitAction;
class AbstractNode;

class ErrorListWidget : public QListWidget
{
public:
    explicit ErrorListWidget(QWidget *parent = nullptr);
    virtual ~ErrorListWidget();

public slots:
    void onAddErrorWidgetItem(AbstractNode* node, const QString& errorMessage, BugType type);
};

#endif // ERRORLISTWIDGET_H
