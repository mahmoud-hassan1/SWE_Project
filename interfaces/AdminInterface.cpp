#include "AdminInterface.h"
#include <iostream>

using namespace std;

AdminInterface::AdminInterface(AdminController* controller) {
    this->controller = controller;
    this->currentAdmin = nullptr;
}

void AdminInterface::setCurrentAdmin(Admin* admin) {
    this->currentAdmin = admin;
}

void AdminInterface::displayMainMenu() {
    int choice;
    
    while (true) {
        cout << "\n========== Admin Menu ==========" << endl;
        cout << "1. View All Courses" << endl;
        cout << "2. Add Course" << endl;
        cout << "3. Edit Course" << endl;
        cout << "4. Delete Course" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                displayCourseDashboard();
                break;
            case 2:
                handleAddCourse();
                break;
            case 3:
                handleEditCourse();
                break;
            case 4:
                handleDeleteCourse();
                break;
            case 5:
                cout << "Logging out..." << endl;
                return;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

void AdminInterface::displayCourseDashboard() {
    vector<Course*>& courses = controller->requestAllCourses();
    
    cout << "\n========== Courses Dashboard ==========" << endl;
    cout << "Code\tName\t\tHours\tCapacity\tRegistered" << endl;
    cout << "------------------------------------------------" << endl;
    
    for (int i = 0; i < courses.size(); i++) {
        cout << courses[i]->getCode() << "\t" 
             << courses[i]->getName() << "\t\t" 
             << courses[i]->getHours() << "\t"
             << courses[i]->getCapacity() << "\t\t"
             << courses[i]->getNumOfRegs() << endl;
    }
    cout << "================================================" << endl;
}

void AdminInterface::handleAddCourse() {
    string name;
    int capacity;
    
    cout << "\n========== Add New Course ==========" << endl;
    cout << "Enter Course Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Capacity: ";
    cin >> capacity;
    
    Course* course = controller->submitNewCourse(name, 3, capacity);
    
    if (course != nullptr) {
        cout << "Course Created Successfully!" << endl;
        cout << "Generated Code: " << course->getCode() << endl;
    } else {
        cout << "Failed to create course. Name might already exist." << endl;
    }
}

void AdminInterface::handleEditCourse() {
    displayCourseDashboard();
    
    string code;
    string name;
    int hours;
    int capacity;
    
    cout << "\nEnter Course Code to Edit: ";
    cin >> code;
    
    cout << "Enter New Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter New Hours: ";
    cin >> hours;
    cout << "Enter New Capacity: ";
    cin >> capacity;
    
    bool success = controller->submitUpdatedCourse(code, name, hours, capacity);
    
    if (success) {
        cout << "Course Updated Successfully!" << endl;
    } else {
        cout << "Failed to update course. Code not found." << endl;
    }
}

void AdminInterface::handleDeleteCourse() {
    displayCourseDashboard();
    
    string code;
    cout << "\nEnter Course Code to Delete: ";
    cin >> code;
    
    bool success = controller->sendDeleteRequest(code);
    
    if (success) {
        cout << "Course Deleted Successfully!" << endl;
    } else {
        cout << "Failed to delete course. Code not found." << endl;
    }
}
