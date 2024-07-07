#include "signup.h"
#include "ui_signup.h"

Signup::Signup(std::map<QString,User> users, QWidget *parent) : QMainWindow(parent) , ui(new Ui::Signup) {
    ui->setupUi(this);

    this->users = users;

    connections();

    hideError();
}

Signup::~Signup() {
    delete ui;
}

void Signup::connections() {
    //click to signup
    connect(ui->pushButtonSignup, SIGNAL(clicked()), this, SLOT(onPushButtonSignupClicked()));

    //click to login
    connect(ui->pushButtonLogin, SIGNAL(clicked()), this, SLOT(onPushButtonLoginClicked()));

    //click to show-hide password
    connect(ui->pushButtonShow, SIGNAL(clicked()), this, SLOT(showPassword()));

    //click enter on line edits to signup
    connect(ui->lineEditFirstName, SIGNAL(returnPressed()), ui->pushButtonSignup, SLOT(click()));
    connect(ui->lineEditLastName, SIGNAL(returnPressed()), ui->pushButtonSignup, SLOT(click()));
    connect(ui->lineEditUsername, SIGNAL(returnPressed()), ui->pushButtonSignup, SLOT(click()));
    connect(ui->lineEditPassword, SIGNAL(returnPressed()), ui->pushButtonSignup, SLOT(click()));

    //set cursor
    ui->lineEditFirstName->setFocus();
}

void Signup::hideError() {
    ui->labelError->hide();
}

void Signup::onPushButtonSignupClicked() {
    if (checkSignup()) {
        addUser();
        onPushButtonLoginClicked();
    }
}

void Signup::onPushButtonLoginClicked() {
    Login *newPage = new Login(users);
    newPage->show();
    this->close();
}

void Signup::showPassword() {
    if (ui->lineEditPassword->echoMode() == QLineEdit::Normal) {
        ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    }
    else {
        ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
    }
}

bool Signup::checkSignup() {
    hideError();

    //check line edits
    if (checkFirstNameField())
        return false;
    if (checkLastNameField())
        return false;
    if (checkUsernameField())
        return false;
    if (checkPasswordField())
        return false;

    return true;
}

bool Signup::checkFirstNameField() {
    if (ui->lineEditFirstName->text() == "") {
        ui->labelError->setText("First Name field is empty");
        ui->labelError->show();
        return true;
    }
    if (checkName(ui->lineEditFirstName->text())) {
        ui->labelError->setText("First Name field is invalid");
        ui->labelError->show();
        return true;
    }
    return false;
}

bool Signup::checkLastNameField() {
    if (ui->lineEditLastName->text() == "") {
        ui->labelError->setText("Last Name field is empty");
        ui->labelError->show();
        return true;
    }
    if (checkName(ui->lineEditLastName->text())) {
        ui->labelError->setText("Last Name field is invalid");
        ui->labelError->show();
        return true;
    }
    return false;
}

bool Signup::checkUsernameField() {
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
    if (checkDuplicateUsername(ui->lineEditUsername->text())) {
        ui->labelError->setText("Username already exists");
        ui->labelError->show();
        return true;
    }
    return false;
}

bool Signup::checkPasswordField() {
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
    return false;
}

bool Signup::checkName(QString name) {
    if (name.size() >= 3 && name.size() <= 15) {
        for (int i = 0; i < name.length(); i++) {
            if ((name[i] < 'A') || (name[i] > 'z') || ((name[i] < 'a') && (name[i] > 'Z'))) {
                return true;
            }
        }
        return false;
    }
    return true;
}

bool Signup::checkLettersNum(QString text) {
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

bool Signup::checkString(QString text) {
    for (int i = 0; i < text.size(); i++) {
        if (((text[i] < 'A') || (text[i] > 'z')) || ((text[i] < 'a') && (text[i] > 'Z'))) {
            if ((text[i] == '.') || (text[i] == '_') || (text[i] == '-') || (text[i] == '!') || (text[i] == '@')
                || ((text[i] >= '0') && (text[i] <='9')))
                continue;
            else
                return true;
        }
    }
    return false;
}

bool Signup::checkDuplicateUsername(QString username) {
    for (auto &itr : users)
        if (itr.first == username)
            return true;
    return false;
}

void Signup::addUser() {
    QString firstName = ui->lineEditFirstName->text();
    QString lastName = ui->lineEditLastName->text();
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    User user;
    user.setFirstName(firstName);
    user.setLastName(lastName);
    user.setUsername(username);
    user.setPassword(password);

    users.insert(std::make_pair(username,user));

    addUserToDatabase(user);
}

void Signup::addUserToDatabase(User user) {
    QSqlDatabase mydb;

    if (!openDatabase(mydb))
        return;

    QSqlQuery query("INSERT INTO users (FirstName, LastName, Username, Password) VALUES"
                    " ('"+user.getFirstName()+"', '"+user.getLastName()+"', '"+user.getUsername()+"', '"+user.getPassword()+"')");
    query.exec();

    closeDatabase(mydb);
}

bool Signup::openDatabase(QSqlDatabase &mydb) {
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("D:/Code/4022/To Do List/uiap-final-project-msm-mir/src/ToDoList.db");

    if (mydb.open())
        return true;
    else
        return false;
}

void Signup::closeDatabase(QSqlDatabase &mydb) {
    mydb.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}
