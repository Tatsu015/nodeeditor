#include "ErrorListWidget.h"
#include "AnalyzeCircuitAction.h"
#include "AbstractNode.h"


ErrorListWidget::ErrorListWidget(QWidget* parent)
{
}

ErrorListWidget::~ErrorListWidget()
{
}

void ErrorListWidget::onAddErrorWidgetItem(AbstractNode* node, const QString& errorMessage, BugType type)
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
