#ifndef ADDLIST_H
#define ADDLIST_H

#include <QMainWindow>
#include "user.h"

namespace Ui { class AddList; }

class AddList : public QMainWindow { Q_OBJECT

public:
    explicit AddList(std::map<QString,User> users, QString username, QWidget *parent = nullptr);
    ~AddList();

    std::map<QString,User> users;
    QString username;

private:
    Ui::AddList *ui;
};

#endif // ADDLIST_H
