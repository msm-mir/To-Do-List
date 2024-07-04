#ifndef USER_H
#define USER_H

#include <QString>

class User {
private:
    QString firstName;
    QString lastName;
    QString username;
    QString password;

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
};

#endif // USER_H
