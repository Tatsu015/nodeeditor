#include "ErrorListWidget.h"
#include "AnalyzeCircuit.h"
#include "Node.h"


ErrorListWidget::ErrorListWidget(QWidget* parent)
{
}

ErrorListWidget::~ErrorListWidget()
{
}

void ErrorListWidget::onAddErrorWidgetItem(Node* node, const QString& errorMessage, BugType type)
{
    QMap<BugType, QString> BUGTYPE_ICONNAME = {
        {Warning, "../resource/warning.png"},
        {Error,   "../resource/error.png"}
    };

    QListWidgetItem* widgetItem = new QListWidgetItem(errorMessage);
    widgetItem->setIcon(QIcon(BUGTYPE_ICONNAME[type]));
    addItem(widgetItem);
    show();
}
