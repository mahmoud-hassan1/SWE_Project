#ifndef STUDENT_H
#define STUDENT_H

#include "Account.h"
#include "Course.h"
#include <vector>
using namespace std;
class Student : public Account {
private:
   vector<Course*> courses;

public:
    Student(string name,string email, string password);

    void regCourse(Course* course);
    void showCourse();
    void dropCourse(Course* course);
    vector<Course*>& getCourses();
    int getCourseCount();
};

#endif