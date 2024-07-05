#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "signup.h"
#include "mainpanel.h"
#include "user.h"

namespace Ui { class Login; }

class Login : public QMainWindow { Q_OBJECT

public:
    explicit Login(std::map<QString,User> users, QWidget *parent = nullptr);
    ~Login();

    std::map<QString,User> users;

    void connections();
    void hideError();
    void openMainPanelPage();
    bool checkLogin();
    bool checkUsernameField();
    bool checkPasswordField();
    bool checkLettersNum(QString);
    bool checkString(QString);
    bool findUsername(QString);
    bool checkMatchPasswordAndUsername(QString, QString);

private slots:
    void onPushButtonLoginClicked();
    void onPushButtonSignupClicked();
    void showPassword();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
