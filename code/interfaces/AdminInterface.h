#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include "../controllers/AdminController.h"
#include "../models/Admin.h"

class AdminInterface {
private:
    AdminController* controller;
    Admin* currentAdmin;

public:
    AdminInterface(AdminController* controller);
    
    void setCurrentAdmin(Admin* admin);
    void displayMainMenu();
    void displayCourseDashboard();
    void handleAddCourse();
    void handleEditCourse();
    void handleDeleteCourse();
};

#endif
