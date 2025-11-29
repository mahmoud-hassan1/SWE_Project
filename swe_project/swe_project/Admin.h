#ifndef ADMIN_H
#define ADMIN_H
#include<vector>
#include "Account.h"
#include "Course.h"
#include "Student.h"
using namespace std;
class Admin : public Account {
public:
    Admin(string name,string email, string password);

    Course* createCourse(string code, string name, int hours, int capacity);
    bool deleteCourse(vector<Course*>& courses, vector<Student*>& students, const string& code);
    void editCourse(Course* course, string name, int hours, int capacity);
};

#endif