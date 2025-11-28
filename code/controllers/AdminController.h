#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include "../system/System.h"
#include "../models/Admin.h"
#include "../models/Course.h"
#include <vector>

class AdminController {
private:
    System* system;

public:
    AdminController(System* system);
    
    Admin* requestAuthentication(std::string email, std::string password);
    std::vector<Course*>& requestAllCourses();
    Course* submitNewCourse(std::string name, int hours, int capacity);
    bool submitUpdatedCourse(std::string code, std::string name, int hours, int capacity);
    bool sendDeleteRequest(std::string code);
};

#endif
