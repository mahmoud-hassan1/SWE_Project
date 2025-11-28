#include "RegistrationController.h"

using namespace std;

RegistrationController::RegistrationController(System* system) {
    this->system = system;
}

Student* RegistrationController::requestAuthentication(string email, string password) {
    return system->findStudent(email, password);
}

vector<Course*>& RegistrationController::requestCourseList() {
    return system->getCourses();
}

bool RegistrationController::submitRegistrationRequest(Student* student, string courseCode) {
    Course* course = system->findCourseByCode(courseCode);
    
    if (course == nullptr) {
        return false;
    }
    
    int studentLoad = student->getCourseCount();
    if (studentLoad >= 6) {
        return false;
    }
    
    int availableCapacity = course->getCapacity() - course->getNumOfRegs();
    if (availableCapacity <= 0) {
        return false;
    }
    
    vector<Course*>& studentCourses = student->getCourses();
    for (int i = 0; i < studentCourses.size(); i++) {
        if (studentCourses[i]->getCode() == courseCode) {
            return false;
        }
    }
    
    student->regCourse(course);
    return true;
}

Course* RegistrationController::getCourseInfo(string courseCode) {
    return system->findCourseByCode(courseCode);
}

int RegistrationController::getStudentCurrentCourses(Student* student) {
    return student->getCourseCount();
}
