#ifndef REGISTRATIONCONTROLLER_H
#define REGISTRATIONCONTROLLER_H

#include "../system/System.h"
#include "../models/Student.h"
#include "../models/Course.h"
#include <vector>

class RegistrationController {
private:
    System* system;

public:
    RegistrationController(System* system);
    
    Student* requestAuthentication(std::string email, std::string password);
    std::vector<Course*>& requestCourseList();
    bool submitRegistrationRequest(Student* student, std::string courseCode);
    Course* getCourseInfo(std::string courseCode);
    int getStudentCurrentCourses(Student* student);
};

#endif
