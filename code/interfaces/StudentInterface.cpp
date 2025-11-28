#include "StudentInterface.h"
#include <iostream>

using namespace std;

StudentInterface::StudentInterface(RegistrationController* controller) {
    this->controller = controller;
    this->currentStudent = nullptr;
}

void StudentInterface::setCurrentStudent(Student* student) {
    this->currentStudent = student;
}

void StudentInterface::displayMainMenu() {
    int choice;
    
    while (true) {
        cout << "\n========== Student Menu ==========" << endl;
        cout << "1. View Available Courses" << endl;
        cout << "2. Register for Course" << endl;
        cout << "3. View My Courses" << endl;
        cout << "4. Drop Course" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                displayCourseTable();
                break;
            case 2:
                handleRegistration();
                break;
            case 3:
                currentStudent->showCourse();
                break;
            case 4:
                handleDropCourse();
                break;
            case 5:
                cout << "Logging out..." << endl;
                return;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

void StudentInterface::displayCourseTable() {
    vector<Course*>& courses = controller->requestCourseList();
    
    cout << "\n========== Available Courses ==========" << endl;
    cout << "Code\tName\t\tCapacity\tAvailable" << endl;
    cout << "----------------------------------------" << endl;
    
    for (int i = 0; i < courses.size(); i++) {
        int available = courses[i]->getCapacity() - courses[i]->getNumOfRegs();
        cout << courses[i]->getCode() << "\t" 
             << courses[i]->getName() << "\t\t" 
             << courses[i]->getCapacity() << "\t\t"
             << available << endl;
    }
    cout << "========================================" << endl;
}

void StudentInterface::handleRegistration() {
    string courseCode;
    
    displayCourseTable();
    
    cout << "Enter Course Code: ";
    cin >> courseCode;
    
    bool success = controller->submitRegistrationRequest(currentStudent, courseCode);
    
    if (success) {
        cout << "Registration Successful!" << endl;
    } else {
        cout << "Cannot Register - Course not found, full, or you reached max courses (6)" << endl;
    }
}

void StudentInterface::handleDropCourse() {
    vector<Course*>& studentCourses = currentStudent->getCourses();
    
    if (studentCourses.size() == 0) {
        cout << "You are not registered in any courses." << endl;
        return;
    }
    
    currentStudent->showCourse();
    
    string courseCode;
    cout << "Enter Course Code to Drop: ";
    cin >> courseCode;
    
    bool found = false;
    for (int i = 0; i < studentCourses.size(); i++) {
        if (studentCourses[i]->getCode() == courseCode) {
            currentStudent->dropCourse(studentCourses[i]);
            cout << "Course dropped successfully." << endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "Course not found in your registered courses." << endl;
    }
}
