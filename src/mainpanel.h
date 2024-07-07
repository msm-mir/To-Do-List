#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFrame>
#include "login.h"
#include "user.h"
#include "addlist.h"
#include "addtask.h"

namespace Ui { class MainPanel; }

class MainPanel : public QMainWindow { Q_OBJECT

public:
    explicit MainPanel(std::map<QString,User> users, QString username, QWidget *parent = nullptr);
    ~MainPanel();

    std::map<QString,User> users;
    QString username;

    void connections();
    void setProfile();
    void addListsWidget(QString, int);
    void addListTasksWidget(QString);
    void addStarTasksWidget(QString);
    void removeWidgets(QFrame*);

private slots:
    void onPushButtonTodayClicked();
    void onPushButtonListsClicked();
    void onPushButtonTasksClicked();
    void onPushButtonStarTasksClicked();
    void onPushButtonCompletedClicked();
    void onPushButtonAssignedMeClicked();
    void onPushButtonAssignedOtherClicked();
    void onPushButtonLogoutClicked();

    void onListClicked(int);
    void openAddListPage();
    void openAddTaskPage(int);

private:
    Ui::MainPanel *ui;
    QVBoxLayout *listLayout;
    QVBoxLayout *listTasksLayout;
    QVBoxLayout *starTasksLayout;
};

#endif // MAINPANEL_H
