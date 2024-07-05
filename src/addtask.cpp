#include "addtask.h"
#include "ui_addtask.h"

AddTask::AddTask(std::map<QString,User> users, QString username, QWidget *parent) : QMainWindow(parent) , ui(new Ui::AddTask) {
    ui->setupUi(this);

    this->users = users;
    this->username = username;
}

AddTask::~AddTask() {
    delete ui;
}
