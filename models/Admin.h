#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"
#include "Course.h"

class Admin : public Account {
public:
    Admin(std::string name, std::string email, std::string password);
    
    Course* createCourse(std::string code, std::string name, int hours, int capacity);
    void deleteCourse(Course* course);
    void editCourse(Course* course, std::string name, int hours, int capacity);
};

#endif
