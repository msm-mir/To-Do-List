#ifndef ADDTASK_H
#define ADDTASK_H

#include <QMainWindow>
#include "user.h"

namespace Ui { class AddTask; }

class AddTask : public QMainWindow { Q_OBJECT

public:
    explicit AddTask(std::map<QString,User> users, QString username, QWidget *parent = nullptr);
    ~AddTask();

    std::map<QString,User> users;
    QString username;

private:
    Ui::AddTask *ui;
};

#endif // ADDTASK_H
