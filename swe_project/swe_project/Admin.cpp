#include "Admin.h"

using namespace std;

Admin::Admin(string name, string email, string password)
    : Account(name, email, password) {
}

Course* Admin::createCourse(string code, string name, int hours, int capacity) {
    return new Course(code, name, hours, capacity);
}

bool Admin::deleteCourse(vector<Course*>& courses, const string& code) {
    for (int i = 0; i < courses.size(); i++) {
        if (courses[i]->getCode() == code) {
            delete courses[i];
            courses.erase(courses.begin() + i);
            return true; 
        }
    }
    return false; 
}

void Admin::editCourse(Course* course, string name, int hours, int capacity) {
    course->setName(name);
    course->setHours(hours);
    course->setCapacity(capacity);
}