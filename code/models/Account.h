#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
protected:
    std::string name;
    std::string email;
    std::string password;

public:
    Account(std::string name, std::string email, std::string password);
    virtual ~Account();
    
    std::string getName();
    std::string getEmail();
    bool login(std::string email, std::string password);
    void setName(std::string name);
    void setEmail(std::string email);
};

#endif
