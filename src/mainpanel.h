#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QtWidgets>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif
#include "user.h"

namespace Ui { class MainPanel; }

class MainPanel : public QMainWindow { Q_OBJECT

public:
    explicit MainPanel(QString callerClass, std::map<QString,User> users, QString username, QWidget *parent = nullptr);
    ~MainPanel();

    std::map<QString,User> users;
    QString username;

    void connections();
    void setProfile();
    void checkReminder();
    void setListTheme(int);
    void addListWidget(List);
    void addTaskWidget(Task, QFrame*);
    void removeWidgets(QHash<QPushButton*,QHBoxLayout*>&);

private slots:
    void onPushButtonTodayClicked();
    void onPushButtonListsClicked();
    void onPushButtonTasksClicked();
    void onPushButtonStarTasksClicked();
    void onPushButtonCompletedClicked();
    void onPushButtonAssignedMeClicked();
    void onPushButtonAssignedOtherClicked();
    void onPushButtonLogoutClicked();

    void getPdf();
    void onListClicked();
    void openAddListPage();
    void openAddTaskPage(int);

private:
    Ui::MainPanel *ui;

    QHash<QPushButton*,QHBoxLayout*> todayLayoutMap;
    QHash<QPushButton*,QHBoxLayout*> listLayoutMap;
    QHash<QPushButton*,QHBoxLayout*> listTasksLayoutMap;
    QHash<QPushButton*,QHBoxLayout*> tasksLayoutMap;
    QHash<QPushButton*,QHBoxLayout*> starTasksLayoutMap;
    QHash<QPushButton*,QHBoxLayout*> completeTasksLayoutMap;
    QHash<QPushButton*,QHBoxLayout*> assignMeLayoutMap;
    QHash<QPushButton*,QHBoxLayout*> assignOtherLayoutMap;

    QHash<QPushButton*,List> listTasksButtonMap;
    QHash<QPushButton*,List> pdfButtonMap;
};

#endif // MAINPANEL_H
