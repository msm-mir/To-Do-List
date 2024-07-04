#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "signup.h"
#include "mainpanel.h"

namespace Ui { class Login; }

class Login : public QMainWindow { Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    void connections();
    void hideError();
    void openMainPanelPage();
    bool checkLogin();
    bool checkUsernameField();
    bool checkPasswordField();
    bool checkLettersNum(QString);
    bool checkString(QString);
    bool findUsername(QString);
    bool checkMatchPasswordAndUsername(QString);

private slots:
    void onPushButtonLoginClicked();
    void onPushButtonSignupClicked();
    void showPassword();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
