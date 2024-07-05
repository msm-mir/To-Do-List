#include "list.h"

List::List() {}
List::~List() {}

void List::setId(int id) {
    this->id = id;
}
int List::getId() {
    return this->id;
}

void List::setUserId(QString userId) {
    this->userId = userId;
}
QString List::getUserId() {
    return this->userId;
}

void List::setName(QString name) {
    this->name = name;
}
QString List::getName() {
    return this->name;
}

void List::setColor(Color color) {
    this->color = color;
}
Color List::getColor() {
    return this->color;
}

void List::addTasks(Task task) {
    this->tasks.pushBack(task);
}
Task List::getTasks(int taskId) {
    Node<Task> *tmp = this->tasks.getHeadNode();

    while (tmp) {
        if (tmp->getData().getId() == taskId)
            return tmp->getData();
        tmp = tmp->getNextNode();
    }

    return Task();
}
