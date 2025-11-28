#include "Account.h"

using namespace std;

Account::Account(string name, string email, string password) {
    this->name = name;
    this->email = email;
    this->password = password;
}

Account::~Account() {
}

string Account::getName() {
    return name;
}

string Account::getEmail() {
    return email;
}

bool Account::login(string email, string password) {
    return (this->email == email && this->password == password);
}

void Account::setName(string name) {
    this->name = name;
}

void Account::setEmail(string email) {
    this->email = email;
}
