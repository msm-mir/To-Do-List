#include "addlist.h"
#include "ui_addlist.h"

AddList::AddList(std::map<QString,User> users, QString username, QWidget *parent) : QMainWindow(parent) , ui(new Ui::AddList) {
    ui->setupUi(this);

    this->users = users;
    this->username = username;
}

AddList::~AddList() {
    delete ui;
}
