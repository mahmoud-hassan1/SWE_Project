#include "System.h"

using namespace std;

System::System() {
    courseCodeCounter = 101;
    
    addCourse(new Course(generateCourseCode(), "Mathematics", 3, 30));
    addCourse(new Course(generateCourseCode(), "Physics", 3, 25));
    addCourse(new Course(generateCourseCode(), "Programming", 4, 20));
    addCourse(new Course(generateCourseCode(), "Database", 3, 25));
    addCourse(new Course(generateCourseCode(), "Networks", 3, 20));
    
    addAdmin(new Admin("Admin", "admin@gmail.com", "admin"));
}

System::~System() {
    for (int i = 0; i < students.size(); i++) {
        delete students[i];
    }
    for (int i = 0; i < admins.size(); i++) {
        delete admins[i];
    }
    for (int i = 0; i < courses.size(); i++) {
        delete courses[i];
    }
}

Student* System::findStudent(string email, string password) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i]->login(email, password)) {
            return students[i];
        }
    }
    return nullptr;
}

Admin* System::findAdmin(string email, string password) {
    for (int i = 0; i < admins.size(); i++) {
        if (admins[i]->login(email, password)) {
            return admins[i];
        }
    }
    return nullptr;
}

bool System::emailExists(string email) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i]->getEmail() == email) {
            return true;
        }
    }
    for (int i = 0; i < admins.size(); i++) {
        if (admins[i]->getEmail() == email) {
            return true;
        }
    }
    return false;
}

void System::addStudent(Student* student) {
    students.push_back(student);
}

void System::addAdmin(Admin* admin) {
    admins.push_back(admin);
}

void System::addCourse(Course* course) {
    courses.push_back(course);
}

void System::removeCourse(Course* course) {
    for (int i = 0; i < courses.size(); i++) {
        if (courses[i]->getCode() == course->getCode()) {
            delete courses[i];
            courses.erase(courses.begin() + i);
            break;
        }
    }
}

vector<Course*>& System::getCourses() {
    return courses;
}

Course* System::findCourseByCode(string code) {
    for (int i = 0; i < courses.size(); i++) {
        if (courses[i]->getCode() == code) {
            return courses[i];
        }
    }
    return nullptr;
}

bool System::courseNameExists(string name) {
    for (int i = 0; i < courses.size(); i++) {
        if (courses[i]->getName() == name) {
            return true;
        }
    }
    return false;
}

string System::generateCourseCode() {
    string code = "C" + to_string(courseCodeCounter);
    courseCodeCounter++;
    return code;
}
