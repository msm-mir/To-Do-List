#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Signup;
}
QT_END_NAMESPACE

class Signup : public QMainWindow
{
    Q_OBJECT

public:
    Signup(QWidget *parent = nullptr);
    ~Signup();

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

private slots:
    void onPushButtonSignupClicked();
    void onPushButtonLoginClicked();
    void showPassword();

private:
    Ui::Signup *ui;
};
#endif // SIGNUP_H
