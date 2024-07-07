#ifndef ADDLIST_H
#define ADDLIST_H

#include <QMainWindow>
#include "user.h"
#include "mainpanel.h"

namespace Ui { class AddList; }

class AddList : public QMainWindow { Q_OBJECT

public:
    explicit AddList(std::map<QString,User> users, QString username, QWidget *parent = nullptr);
    ~AddList();

    std::map<QString,User> users;
    QString username;

    void connections();
    void hideError();
    bool checkAddList();
    bool checkListNameField();
    bool checkListColorButton();
    bool checkName(QString);
    bool checkDuplicateName(QString);
    void addList();
    void addListToDatabase(List);
    bool openDatabase(QSqlDatabase &mydb);
    void closeDatabase(QSqlDatabase &mydb);

private slots:
    void openMainPanelPage();
    void onPushButtonAddListClicked();
    void setBlueBackgroundIcon(bool);
    void setGreenBackgroundIcon(bool);
    void setPinkBackgroundIcon(bool);
    void setPurpleBackgroundIcon(bool);

private:
    Ui::AddList *ui;
};

#endif // ADDLIST_H
