#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;
class Account {
protected:
    string name;
    string email;
    string password;

public:
    Account(string name, string email, string password);
    virtual ~Account();

    string getName();
    string getEmail();
    bool login(std::string email, std::string password);
    void setName(std::string name);
    void setEmail(std::string email);
};

#endif