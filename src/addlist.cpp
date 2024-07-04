#include "addlist.h"
#include "ui_addlist.h"

AddList::AddList(QWidget *parent) : QMainWindow(parent) , ui(new Ui::AddList) {
    ui->setupUi(this);
}

AddList::~AddList() {
    delete ui;
}
