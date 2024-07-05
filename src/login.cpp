#include "login.h"
#include "ui_login.h"

Login::Login(std::map<QString,User> users, QWidget *parent) : QMainWindow(parent) , ui(new Ui::Login) {
    ui->setupUi(this);

    this->users = users;

    connections();

    hideError();
}

Login::~Login() {
    delete ui;
}

void Login::connections() {
    //click to login
    connect(ui->pushButtonLogin, SIGNAL(clicked()), this, SLOT(onPushButtonLoginClicked()));

    //click to signup
    connect(ui->pushButtonSignup, SIGNAL(clicked()), this, SLOT(onPushButtonSignupClicked()));

    //click to show-hide password
    connect(ui->pushButtonShow, SIGNAL(clicked()), this, SLOT(showPassword()));

    //click enter on line edits to signup
    connect(ui->lineEditUsername, SIGNAL(returnPressed()), ui->pushButtonLogin, SLOT(click()));
    connect(ui->lineEditPassword, SIGNAL(returnPressed()), ui->pushButtonLogin, SLOT(click()));

    //set cursor
    ui->lineEditUsername->setFocus();
}

void Login::hideError() {
    ui->labelError->hide();
}

void Login::onPushButtonLoginClicked() {
    if (checkLogin()) {
        openMainPanelPage();
    }
}

void Login::openMainPanelPage() {
    MainPanel *newPage = new MainPanel(users);
    newPage->show();
    this->close();
}

void Login::onPushButtonSignupClicked() {
    Signup *newPage = new Signup(users);
    newPage->show();
    this->close();
}

void Login::showPassword() {
    if (ui->lineEditPassword->echoMode() == QLineEdit::Normal) {
        ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    }
    else {
        ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
    }
}

bool Login::checkLogin() {
    hideError();

    //check line edits
    if (checkUsernameField())
        return false;
    if (checkPasswordField())
        return false;

    return true;
}

bool Login::checkUsernameField() {
    if (ui->lineEditUsername->text() == "") {
        ui->labelError->setText("Username field is empty");
        ui->labelError->show();
        return true;
    }
    if (checkLettersNum(ui->lineEditUsername->text())) {
        ui->labelError->setText("Username field must be more than 4 characters");
        ui->labelError->show();
        return true;
    }
    if (checkString(ui->lineEditUsername->text())) {
        ui->labelError->setText("Username field is invalid");
        ui->labelError->show();
        return true;
    }
    if (findUsername(ui->lineEditUsername->text())) {
        ui->labelError->setText("Username doesn't exist");
        ui->labelError->show();
        return true;
    }
    return false;
}

bool Login::checkPasswordField() {
    if (ui->lineEditPassword->text() == "") {
        ui->labelError->setText("Password field is empty");
        ui->labelError->show();
        return true;
    }
    if (checkLettersNum(ui->lineEditPassword->text())) {
        ui->labelError->setText("Password field must be more than 4 characters");
        ui->labelError->show();
        return true;
    }
    if (checkString(ui->lineEditPassword->text())) {
        ui->labelError->setText("Password field is invalid");
        ui->labelError->show();
        return true;
    }
    if (checkMatchPasswordAndUsername(ui->lineEditUsername->text(), ui->lineEditPassword->text())) {
        ui->labelError->setText("Password is incorrect");
        ui->labelError->show();
        return true;
    }
    return false;
}

bool Login::checkLettersNum(QString text) {
    int cntLetter = 0;
    for (int i = 0; i < text.size(); i++) {
        if (((text[i] >= 'A') && (text[i] <= 'Z')) || ((text[i] >= 'a') && (text[i] <= 'z'))) {
            cntLetter++;
        }
    }
    if (cntLetter >= 4) {
        return false;
    }
    return true;
}

bool Login::checkString(QString text) {
    for (int i = 0; i < text.size(); i++) {
        if (((text[i] < '!') || (text[i] > 'z')) || ((text[i] < 'a') && (text[i] > 'Z'))) {
            if ((text[i] == '.') || (text[i] == '_') || (text[i] == '-') || (text[i] == '!') || (text[i] == '@')
                || ((text[i] >= '0') && (text[i] <='9')))
                continue;
            else
                return true;
        }
    }
    return false;
}

bool Login::findUsername(QString text) {
    if (users.find(text) != users.end())
        return false;
    return true;
}

bool Login::checkMatchPasswordAndUsername(QString username, QString password) {
    for (std::pair<QString,User> itr : users) {
        if (itr.first == username)
            if (itr.second.getPassword() == password)
                return false;
    }
    return true;
}
