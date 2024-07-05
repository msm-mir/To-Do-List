#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include "login.h"
#include "user.h"

namespace Ui { class MainPanel; }

class MainPanel : public QMainWindow { Q_OBJECT

public:
    explicit MainPanel(std::map<QString,User> users, QString username, QWidget *parent = nullptr);
    ~MainPanel();

    std::map<QString,User> users;
    QString username;

    void connections();

private slots:
    void onPushButtonTodayClicked();
    void onPushButtonListsClicked();
    void onPushButtonTasksClicked();
    void onPushButtonStarTasksClicked();
    void onPushButtonCompletedClicked();
    void onPushButtonAssignedMeClicked();
    void onPushButtonAssignedOtherClicked();
    void onPushButtonLogoutClicked();

    void onListClicked();

    void addListsWidget();
    void addListTasksWidget();

    void removeWidgets();

private:
    Ui::MainPanel *ui;

    QHash<QPushButton*, QHBoxLayout*> mButtonToLayoutMap;
};

#endif // MAINPANEL_H
