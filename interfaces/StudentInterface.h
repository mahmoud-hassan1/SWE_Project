#ifndef STUDENTINTERFACE_H
#define STUDENTINTERFACE_H

#include "../controllers/RegistrationController.h"
#include "../models/Student.h"

class StudentInterface {
private:
    RegistrationController* controller;
    Student* currentStudent;

public:
    StudentInterface(RegistrationController* controller);
    
    void setCurrentStudent(Student* student);
    void displayMainMenu();
    void displayCourseTable();
    void handleRegistration();
    void handleDropCourse();
};

#endif
