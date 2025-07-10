#include "addlist.h"
#include "ui_addlist.h"
#include "mainpanel.h"
#include <QSqlQuery>

AddList::AddList(std::map<QString,User> users, QString username, QWidget *parent) : QMainWindow(parent) , ui(new Ui::AddList) {
    ui->setupUi(this);

    this->users = users;
    this->username = username;

    connections();

    hideError();
}

AddList::~AddList() {
    delete ui;
}

void AddList::connections() {
    //click to add list
    connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(onPushButtonAddListClicked()));

    //click cancel
    connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(openMainPanelPage()));

    //click to select color
    connect(ui->pushButtonBlue, SIGNAL(toggled(bool)), this, SLOT(setBlueBackgroundIcon(bool)));
    connect(ui->pushButtonGreen, SIGNAL(toggled(bool)), this, SLOT(setGreenBackgroundIcon(bool)));
    connect(ui->pushButtonPink, SIGNAL(toggled(bool)), this, SLOT(setPinkBackgroundIcon(bool)));
    connect(ui->pushButtonPurple, SIGNAL(toggled(bool)), this, SLOT(setPurpleBackgroundIcon(bool)));

    //click enter on line edits to add list
    connect(ui->lineEditListName, SIGNAL(returnPressed()), ui->pushButtonAdd, SLOT(click()));

    //set cursor
    ui->lineEditListName->setFocus();
}

void AddList::hideError() {
    ui->labelError->hide();
}

void AddList::onPushButtonAddListClicked() {
    if (checkAddList()) {
        addList();
        openMainPanelPage();
    }
}

bool AddList::checkAddList() {
    hideError();

    //check line edits
    if (checkListNameField())
        return false;
    if (checkListColorButton())
        return false;

    return true;
}

bool AddList::checkListNameField() {
    if (ui->lineEditListName->text() == "") {
        ui->labelError->setText("List Name field is empty");
        ui->labelError->show();
        return true;
    }
    if (checkName(ui->lineEditListName->text())) {
        ui->labelError->setText("List Name field is invalid");
        ui->labelError->show();
        return true;
    }
    if (checkDuplicateName(ui->lineEditListName->text())) {
        ui->labelError->setText("List Name already exists");
        ui->labelError->show();
        return true;
    }
    return false;
}

bool AddList::checkListColorButton() {
    if ((!ui->pushButtonBlue->isChecked()) && (!ui->pushButtonGreen->isChecked()) &&
        (!ui->pushButtonPink->isChecked()) && (!ui->pushButtonPurple->isChecked())) {
        ui->labelError->setText("Color button isn't selected");
        ui->labelError->show();
        return true;
    }
    return false;
}

bool AddList::checkName(QString text) {
    for (int i = 0; i < text.size(); i++) {
        if (((text[i] < 'A') || (text[i] > 'z')) || ((text[i] < 'a') && (text[i] > 'Z'))) {
            if ((text[i] >= '0') && (text[i] <='9'))
                continue;
            else
                return true;
        }
    }
    return false;
}

bool AddList::checkDuplicateName(QString name) {
    for (auto &itr : users)
        if (itr.first == username)
            for (int i = 0; i < itr.second.getListsSize(); i++)
                if (itr.second.getLists(i).getName() == name)
                    return true;
    return false;
}

void AddList::setBlueBackgroundIcon(bool checked) {
    QPixmap blue(":/images/background/small_background_blue.png");

    if (checked)
        ui->labelBackground->setPixmap(blue);
}

void AddList::setGreenBackgroundIcon(bool checked) {
    QPixmap green(":/images/background/small_background_green.png");

    if (checked)
        ui->labelBackground->setPixmap(green);
}

void AddList::setPinkBackgroundIcon(bool checked) {
    QPixmap pink(":/images/background/small_background_pink.png");

    if (checked)
        ui->labelBackground->setPixmap(pink);
}

void AddList::setPurpleBackgroundIcon(bool checked) {
    QPixmap purple(":/images/background/small_background_purple.png");

    if (checked)
        ui->labelBackground->setPixmap(purple);
}

void AddList::openMainPanelPage() {
    MainPanel *newPage = new MainPanel(users, username);
    newPage->show();
    this->close();
}

void AddList::addList() {
    QString listName = ui->lineEditListName->text();

    Color color = none;
    if (ui->pushButtonBlue->isChecked())
        color = blue;
    else if (ui->pushButtonGreen->isChecked())
        color = green;
    else if (ui->pushButtonPink->isChecked())
        color = pink;
    else if (ui->pushButtonPurple->isChecked())
        color = purple;

    List list;
    list.setName(listName);
    list.setColor(color);
    list.setUserId(username);

    for (auto &itr : users)
        if (itr.first == username) {
            list.setId(itr.second.getListsSize() + 1);
            itr.second.setLists(itr.second.getListsSize() + 1, list);
        }

    addListToDatabase(list);
}

void AddList::addListToDatabase(List list) {
    QSqlDatabase mydb;

    if (!openDatabase(mydb))
        return;

    QSqlQuery query;
    query.prepare("INSERT INTO lists (UserId, ListId, Name, Color) VALUES (:username, :listId, :name, :color)");
    query.bindValue(":username", username);
    query.bindValue(":listId", list.getId());
    query.bindValue(":name", list.getName());
    query.bindValue(":color", QString::number(static_cast<int>(list.getColor())));
    query.exec();

    closeDatabase(mydb);
}

bool AddList::openDatabase(QSqlDatabase &mydb) {
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("D:/Code/4022/To Do List/uiap-final-project-msm-mir/src/ToDoList.db");

    if (!mydb.open())
        return false;
    else
        return true;
}

void AddList::closeDatabase(QSqlDatabase &mydb) {
    mydb.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}
