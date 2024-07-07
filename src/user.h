#ifndef USER_H
#define USER_H

#include <QString>
#include <map>
#include "list.h"

class User {
private:
    QString firstName;
    QString lastName;
    QString username;
    QString password;
    std::map<int,List> lists;

public:
    User();
    ~User();

    void setFirstName(QString);
    QString getFirstName();

    void setLastName(QString);
    QString getLastName();

    void setUsername(QString);
    QString getUsername();

    void setPassword(QString);
    QString getPassword();

    void setLists(int, List);
    List getLists(int);

    int getListsSize();
};

#endif // USER_H
