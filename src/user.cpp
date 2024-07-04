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
