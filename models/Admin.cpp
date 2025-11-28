#include "Admin.h"

using namespace std;

Admin::Admin(string name, string email, string password)
    : Account(name, email, password) {
}

Course* Admin::createCourse(string code, string name, int hours, int capacity) {
    return new Course(code, name, hours, capacity);
}

void Admin::deleteCourse(Course* course) {
}

void Admin::editCourse(Course* course, string name, int hours, int capacity) {
    course->setName(name);
    course->setHours(hours);
    course->setCapacity(capacity);
}
