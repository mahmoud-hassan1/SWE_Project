#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"
#include "Course.h"
using namespace std;
class Admin : public Account {
public:
    Admin(string name,string email, string password);

    Course* createCourse(string code, string name, int hours, int capacity);
    void deleteCourse(Course* course);
    void editCourse(Course* course, string name, int hours, int capacity);
};

#endif