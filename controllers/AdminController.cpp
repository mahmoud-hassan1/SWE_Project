#include "AdminController.h"

using namespace std;

AdminController::AdminController(System* system) {
    this->system = system;
}

Admin* AdminController::requestAuthentication(string email, string password) {
    return system->findAdmin(email, password);
}

vector<Course*>& AdminController::requestAllCourses() {
    return system->getCourses();
}

Course* AdminController::submitNewCourse(string name, int hours, int capacity) {
    if (system->courseNameExists(name)) {
        return nullptr;
    }
    
    string code = system->generateCourseCode();
    Course* course = new Course(code, name, hours, capacity);
    system->addCourse(course);
    return course;
}

bool AdminController::submitUpdatedCourse(string code, string name, int hours, int capacity) {
    Course* course = system->findCourseByCode(code);
    if (course == nullptr) {
        return false;
    }
    
    course->setName(name);
    course->setHours(hours);
    course->setCapacity(capacity);
    return true;
}

bool AdminController::sendDeleteRequest(string code) {
    Course* course = system->findCourseByCode(code);
    if (course == nullptr) {
        return false;
    }
    
    system->removeCourse(course);
    return true;
}
