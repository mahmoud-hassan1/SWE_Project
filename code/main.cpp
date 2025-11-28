#include "system/System.h"
#include "controllers/RegistrationController.h"
#include "controllers/AdminController.h"
#include "interfaces/LoginInterface.h"
#include "interfaces/StudentInterface.h"
#include "interfaces/AdminInterface.h"

int main() {
    System* system = new System();
    
    RegistrationController* regController = new RegistrationController(system);
    AdminController* adminController = new AdminController(system);
    
    StudentInterface* studentInterface = new StudentInterface(regController);
    AdminInterface* adminInterface = new AdminInterface(adminController);
    
    LoginInterface* loginInterface = new LoginInterface(system, regController, adminController,
                                                         studentInterface, adminInterface);
    
    loginInterface->displayMenu();
    
    delete loginInterface;
    delete adminInterface;
    delete studentInterface;
    delete adminController;
    delete regController;
    delete system;
    
    return 0;
}
