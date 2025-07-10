#ifndef ADDTASK_H
#define ADDTASK_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "user.h"

namespace Ui { class AddTask; }

class AddTask : public QMainWindow { Q_OBJECT

public:
    explicit AddTask(std::map<QString,User> users, QString username, int listId, QWidget *parent = nullptr);
    ~AddTask();

    std::map<QString,User> users;
    QString username;
    int listId;

    void connections();
    void hideError();
    bool checkAddTask();
    bool checkTaskNameField();
    bool checkDateField();
    bool checkDetailsField();
    bool checkAssignField();
    bool checkName(QString);
    bool checkString(QString);
    bool checkDuplicateName(QString);
    bool findUsername(QString);
    void addTask();
    void addTaskToDatabase(Task);
    bool openDatabase(QSqlDatabase &mydb);
    void closeDatabase(QSqlDatabase &mydb);

private slots:
    void onPushButtonAddTaskClicked();
    void openMainPanelPage();

private:
    Ui::AddTask *ui;
};

#endif // ADDTASK_H
