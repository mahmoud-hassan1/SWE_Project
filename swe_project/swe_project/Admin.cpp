#include "Admin.h"

using namespace std;

Admin::Admin(string name, string email, string password)
    : Account(name, email, password) {}

Course *Admin::createCourse(string code, string name, int hours, int capacity) {
  return new Course(code, name, hours, capacity);
}

bool Admin::deleteCourse(vector<Course *> &courses, vector<Student *> &students,
                         const string &code) {
  for (int i = 0; i < courses.size(); i++) {
    if (courses[i]->getCode() == code) {

      for (auto student : students) {
        for (int j = 0; j < student->getCourses().size(); j++) {
          if (student->getCourses()[j]->getCode() == code) {
            student->getCourses().erase(student->getCourses().begin() + j);
            break;
          }
        }
      }

      delete courses[i];
      courses.erase(courses.begin() + i);
      return true;
    }
  }
  return false;
}

void Admin::editCourse(Course *course, string name, int hours, int capacity) {
  course->setName(name);
  course->setHours(hours);
  course->setCapacity(capacity);
}
