#ifndef BUILDER_H
#define BUILDER_H

#include <QObject>
#include <QMap>
#include <QString>

class QAction;
class QToolButton;
class MainWindow;

namespace Ui {
    class MainWindow;
}

class Builder : public QObject
{

private:
    struct ToolBarAction
    {
        QAction* m_action     = nullptr;
        QToolButton* m_button = nullptr;
    };

public:
    static Builder* getInstance();
    void build(MainWindow* mainWindow, Ui::MainWindow* ui);


private:
    void buildGraphicsView(MainWindow* mainWindow, Ui::MainWindow* ui);
    void buildMenu(MainWindow* mainWindow, Ui::MainWindow* ui);
    void buildToolBar(MainWindow* mainWindow, Ui::MainWindow* ui);
    void buildDockWidget(MainWindow* mainWindow, Ui::MainWindow* ui);

    void setDefaultToolBarAction(QString actionName);

private slots:
    void onChangeTool();

private:
    QMap<QString, ToolBarAction*> m_toolBarActions;

private:
    Builder(QObject *parent=nullptr);
    ~Builder();
};

#endif // BUILDER_H
