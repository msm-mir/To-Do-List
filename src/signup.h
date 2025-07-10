#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <map>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Signup; }
QT_END_NAMESPACE

class Signup : public QMainWindow { Q_OBJECT

public:
    Signup(std::map<QString,User> users, QWidget *parent = nullptr);
    ~Signup();

    std::map<QString,User> users;

    void connections();
    void hideError();
    bool checkSignup();

    bool checkFirstNameField();
    bool checkLastNameField();
    bool checkUsernameField();
    bool checkPasswordField();

    bool checkName(QString);
    bool checkLettersNum(QString);
    bool checkString(QString);
    bool checkDuplicateUsername(QString);

    void addUser();
    void addUserToDatabase(User);
    bool openDatabase(QSqlDatabase &mydb);
    void closeDatabase(QSqlDatabase &mydb);

private slots:
    void onPushButtonSignupClicked();
    void onPushButtonLoginClicked();
    void showPassword();

private:
    Ui::Signup *ui;
};
#endif // SIGNUP_H
