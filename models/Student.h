#ifndef STUDENT_H
#define STUDENT_H

#include "Account.h"
#include "Course.h"
#include <vector>

class Student : public Account {
private:
    std::vector<Course*> courses;

public:
    Student(std::string name, std::string email, std::string password);
    
    void regCourse(Course* course);
    void showCourse();
    void dropCourse(Course* course);
    std::vector<Course*>& getCourses();
    int getCourseCount();
};

#endif
