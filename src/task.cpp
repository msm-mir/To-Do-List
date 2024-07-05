#include "task.h"

Task::Task() {}
Task::~Task() {}

void Task::setId(int id) {
    this->id = id;
}
int Task::getId() {
    return this->id;
}

void Task::setListId(int listId) {
    this->listId = listId;
}
int Task::getListId() {
    return this->listId;
}

void Task::setName(QString name) {
    this->name = name;
}
QString Task::getName() {
    return this->name;
}

void Task::setDate(QDate date) {
    this->date = date;
}
QDate Task::getDate() {
    return this->date;
}

void Task::setDetail(QString detail) {
    this->detail = detail;
}
QString Task::getDetail() {
    return this->detail;
}

void Task::setAssign(QString assign) {
    this->assign = assign;
}
QString Task::getAssign() {
    return this->assign;
}

void Task::setStar(bool star) {
    this->star = star;
}
bool Task::getStar() {
    return this->star;
}

void Task::setComplete(bool complete) {
    this->complete = complete;
}
bool Task::getComplete() {
    return this->complete;
}
