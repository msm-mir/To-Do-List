#include "signup.h"
#include "login.h"
#include "mainpanel.h"
#include "addlist.h"
#include "addtask.h"
#include "user.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>

bool openDatabase(QSqlDatabase &mydb);
void closeDatabase(QSqlDatabase &mydb);
void databaseToMap(QSqlDatabase &mydb, std::map<QString,User> &users, std::map<int,List> &lists, std::map<int,Task> &tasks);
void setTask(std::map<int,Task> &tasks);
void setList(std::map<int,List> &lists, std::map<int,Task> &tasks);
void setUser(std::map<QString,User> &users, std::map<int,List> &lists);

int main(int argc, char *argv[]) {
    QApplication z(argc, argv);

    QSqlDatabase mydb;

    std::map<int,Task> tasks;
    std::map<int,List> lists;
    std::map<QString,User> users;

    if (!openDatabase(mydb))
        return -1;

    databaseToMap(mydb, users, lists, tasks);

    Signup a(users);
    a.show();

    return z.exec();
}

bool openDatabase(QSqlDatabase &mydb) {
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("D:/Code/4022/To Do List/To-Do-List/src/ToDoList.db");

    if (mydb.open())
        return true;
    else
        return false;
}

void closeDatabase(QSqlDatabase &mydb) {
    mydb.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

void databaseToMap(QSqlDatabase &mydb, std::map<QString,User> &users, std::map<int,List> &lists, std::map<int,Task> &tasks) {
    setTask(tasks);
    setList(lists, tasks);
    setUser(users, lists);

    closeDatabase(mydb);
}

void setTask(std::map<int,Task> &tasks) {
    QSqlQuery query("SELECT * FROM tasks");

    while (query.next()) {
        int listId = query.value(0).toInt();
        int taskId = query.value(1).toInt();
        QString name = query.value(2).toString();
        QDate date = QDate::fromString(query.value(3).toString(), Qt::ISODate);
        QString details = query.value(4).toString();
        QString assign = query.value(5).toString();
        bool star = query.value(6).toInt();
        bool complete = query.value(7).toInt();

        Task task;
        task.setId(taskId);
        task.setListId(listId);
        task.setName(name);
        task.setDate(date);
        task.setDetail(details);
        task.setAssign(assign);
        task.setStar(star);
        task.setComplete(complete);

        tasks.insert(std::make_pair(taskId,task));
    }
}

void setList(std::map<int,List> &lists, std::map<int,Task> &tasks) {
    QSqlQuery query("SELECT * FROM lists");

    while (query.next()) {
        QString userId = query.value(0).toString();
        int listId = query.value(1).toInt();
        QString name = query.value(2).toString();
        Color color = static_cast<Color>(query.value(3).toInt());

        List list;
        list.setId(listId);
        list.setUserId(userId);
        list.setName(name);
        list.setColor(color);

        for (auto &itr : tasks)
            if (itr.second.getListId() == listId)
                list << itr.second;

        lists.insert(std::make_pair(listId,list));
    }
}

void setUser(std::map<QString,User> &users, std::map<int,List> &lists) {
    QSqlQuery query("SELECT * FROM users");

    while (query.next()) {
        QString firstName = query.value(0).toString();
        QString lastName = query.value(1).toString();
        QString username = query.value(2).toString();
        QString password = query.value(3).toString();

        User user;
        user.setFirstName(firstName);
        user.setLastName(lastName);
        user.setUsername(username);
        user.setPassword(password);

        for (auto &itr : lists) {
            if (itr.second.getUserId() == username)
                user.setLists(itr.first, itr.second);
        }


        users.insert(std::make_pair(username,user));
    }
}
