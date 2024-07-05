#include "user.h"

User::User() {}
User::~User() {}

void User::setFirstName(QString firstName) {
    this->firstName = firstName;
}
QString User::getFirstName() {
    return this->firstName;
}

void User::setLastName(QString lastName) {
    this->lastName = lastName;
}
QString User::getLastName() {
    return this->lastName;
}

void User::setUsername(QString username) {
    this->username = username;
}
QString User::getUsername() {
    return this->username;
}

void User::setPassword(QString password) {
    this->password = password;
}
QString User::getPassword() {
    return this->password;
}

void User::setLists(int listId, List list) {
    this->lists.insert(std::make_pair(listId, list));
}
List User::getLists(int listId) {
    for (const auto &itr: this->lists)
        if (itr.first == listId)
            return itr.second;
    return List();
}
