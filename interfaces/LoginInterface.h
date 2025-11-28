#ifndef LOGININTERFACE_H
#define LOGININTERFACE_H

#include "../system/System.h"
#include "../controllers/RegistrationController.h"
#include "../controllers/AdminController.h"
#include "StudentInterface.h"
#include "AdminInterface.h"

class LoginInterface {
private:
    System* system;
    RegistrationController* regController;
    AdminController* adminController;
    StudentInterface* studentInterface;
    AdminInterface* adminInterface;

    bool isValidEmail(std::string email);

public:
    LoginInterface(System* system, RegistrationController* regController, 
                   AdminController* adminController, StudentInterface* studentInterface,
                   AdminInterface* adminInterface);
    
    void displayMenu();
    void handleLogin();
    void handleSignup();
};

#endif
