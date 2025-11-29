#include "Student.h"
#include <iostream>

using namespace std;

Student::Student(string name, string email, string password)
    : Account(name, email, password) {}

void Student::regCourse(Course *course) {
  if (courses.size() < 6) {
    courses.push_back(course);
    course->incrementRegister();
  } else {
    cout << "you have the maximum amount of courses per semester\n";
  }
}

void Student::showCourse() {
  cout << "Your Registered Courses:" << endl;
  cout << "----------------------------------------" << endl;
  for (int i = 0; i < courses.size(); i++) {
    cout << courses[i]->getCode() << " - " << courses[i]->getName() << endl;
  }
  cout << "----------------------------------------" << endl;
}

void Student::dropCourse(Course *course) {
  for (int i = 0; i < courses.size(); i++) {
    if (courses[i]->getCode() == course->getCode()) {
      courses.erase(courses.begin() + i);
      course->decrementRegister();
      break;
    }
  }
}

vector<Course *> &Student::getCourses() { return courses; }

int Student::getCourseCount() { return courses.size(); }