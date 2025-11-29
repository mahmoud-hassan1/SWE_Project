#include <iostream>
#include <limits>
#include <vector>
using namespace std;

#include "Admin.h"
#include "Course.h"
#include "Student.h"

void clearInput() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isValidEmail(const string &email) {
  size_t atPos = email.find('@');
  if (atPos == string::npos || atPos == 0 || atPos == email.length() - 1) {
    return false;
  }

  size_t dotPos = email.find('.', atPos);
  if (dotPos == string::npos || dotPos == atPos + 1 || dotPos == email.length() - 1) {
    return false;
  }

  if (email.find(' ') != string::npos) {
    return false;
  }

  if (email.find('@', atPos + 1) != string::npos) {
    return false;
  }

  return true;
}

void line() { cout << "----------------------------------------\n"; }

void printHeader(const string &title) {
  cout << "\n========================================\n"
       << "         " << title << "\n"
       << "========================================\n";
}

void printSuccess(const string &msg) { cout << "[OK] " << msg << "\n"; }

void printError(const string &msg) { cout << "[ERROR] " << msg << "\n"; }

void printOption(int num, const string &text) {
  cout << num << ". " << text << "\n";
}

Student *findStudent(vector<Student *> &students, const string &email,
                     const string &pass) {
  for (auto s : students)
    if (s->login(email, pass))
      return s;
  return nullptr;
}

Course *findCourse(vector<Course *> &courses, const string &code) {
  for (auto c : courses)
    if (c->getCode() == code)
      return c;
  return nullptr;
}

void signUp(vector<Student *> &students) {
  printHeader("SIGN UP");

  string name, email, pass;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Enter your name: ";
  getline(cin, name);

  cout << "Enter your email: ";
  getline(cin, email);

  if (!isValidEmail(email)) {
    printError("Invalid email format! Please use a valid email (e.g., user@example.com)");
    return;
  }

  cout << "Enter password: ";
  getline(cin, pass);

  students.push_back(new Student(name, email, pass));

  printSuccess("Account created successfully!");
}

void adminMenu(Admin &admin, vector<Course *> &courses,
               vector<Student *> &students) {
  printHeader("ADMIN PANEL");

  while (true) {
    printOption(1, "Create Course");
    printOption(2, "Edit Course");
    printOption(3, "Delete Course");
    printOption(4, "Show All Courses");
    printOption(5, "Logout");

    cout << "Choose: ";
    int c;
    cin >> c;

    if (cin.fail()) {
      clearInput();
      printError("Invalid input!");
      continue;
    }

    if (c == 1) {
      string code, name;
      int hours, cap;

      cout << "Enter course code: ";
      cin >> code;

      if (findCourse(courses, code)) {
        printError("Course code already exists.");
        continue;
      }

      cout << "Enter course name: ";
      cin.ignore();
      getline(cin, name);
      cout << "Enter hours: ";
      cin >> hours;
      if (cin.fail()) {
        clearInput();
        printError("Invalid hours!");
        continue;
      }
      cout << "Enter capacity: ";
      cin >> cap;
      if (cin.fail()) {
        clearInput();
        printError("Invalid capacity!");
        continue;
      }

      Course *newCourse = admin.createCourse(code, name, hours, cap);
      courses.push_back(newCourse);
      printSuccess("Course created!");
    }

    else if (c == 2) {
      string code;
      cout << "Enter course code to edit: ";
      cin >> code;

      Course *target = findCourse(courses, code);
      if (!target) {
        printError("Course not found!");
        continue;
      }

      string name;
      int hours, cap;
      cout << "Enter new name: ";
      cin.ignore();
      getline(cin, name);
      cout << "Enter new hours: ";
      cin >> hours;
      if (cin.fail()) {
        clearInput();
        printError("Invalid hours!");
        continue;
      }
      cout << "Enter new capacity: ";
      cin >> cap;
      if (cin.fail()) {
        clearInput();
        printError("Invalid capacity!");
        continue;
      }

      admin.editCourse(target, name, hours, cap);
      printSuccess("Course updated!");
    }

    else if (c == 3) {
      string code;
      cout << "Enter course code to delete: ";
      cin >> code;

      if (admin.deleteCourse(courses, students, code))
        printSuccess("Course deleted!");
      else
        printError("Course not found!");
    }

    else if (c == 4) {
      printHeader("ALL COURSES");

      for (auto c : courses) {
        cout << c->getCode() << " | " << c->getName() << " | " << c->getHours()
             << "h"
             << " | Cap: " << c->getCapacity()
             << " | Regs: " << c->getNumOfRegs()
             << " | Available: " << boolalpha << c->IsAvaliable() << "\n";
      }
    }

    else if (c == 5) {
      printSuccess("Logged out.");
      break;
    }
  }
}

void studentMenu(Student *logged, vector<Course *> &courses) {
  printHeader("STUDENT PANEL");

  while (true) {
    printOption(1, "Register Course");
    printOption(2, "Drop Course");
    printOption(3, "Show My Courses");
    printOption(4, "Show Available Courses");
    printOption(5, "Logout");

    cout << "Choose: ";
    int c;
    cin >> c;

    if (cin.fail()) {
      clearInput();
      printError("Invalid input!");
      continue;
    }

    if (c == 1) {
      string code;
      cout << "Enter course code: ";
      cin >> code;

      Course *target = nullptr;
      for (auto crs : courses)
        if (crs->getCode() == code)
          target = crs;

      if (!target) {
        printError("Course not found!");
        continue;
      }

      if (!target->IsAvaliable()) {
        printError("Course is full!");
        continue;
      }

      bool already = false;
      for (auto crs : logged->getCourses()) {
        if (crs->getCode() == code) {
          already = true;
          break;
        }
      }

      if (already) {
        printError("You are already registered in this course!");
        continue;
      }

      logged->regCourse(target);
      printSuccess("Course registered!");
    }

    else if (c == 2) {
      string code;
      cout << "Enter course code to drop: ";
      cin >> code;

      Course *target = nullptr;

      for (auto crs : logged->getCourses()) {
        if (crs->getCode() == code) {
          target = crs;
          break;
        }
      }

      if (!target) {
        printError("You are not registered in this course!");
        continue;
      }

      logged->dropCourse(target);
      printSuccess("Course dropped!");
    }

    else if (c == 3) {
      printHeader("MY COURSES");
      logged->showCourse();
    }

    else if (c == 4) {
      printHeader("AVAILABLE COURSES");

      for (auto c : courses) {
        if (c->IsAvaliable()) {
          cout << c->getCode() << " - " << c->getName()
               << " (hours: " << c->getHours()
               << "\tCapacity: " << c->getCapacity()
               << "\tRegs: " << c->getNumOfRegs() << ")\n";
        }
      }
    }

    else if (c == 5) {
      printSuccess("Logged out.");
      break;
    }
  }
}

int main() {
  Admin admin("Admin", "admin@system.com", "123");
  vector<Student *> students;
  vector<Course *> courses;

  courses.push_back(new Course("CS101", "Intro to CS", 3, 50));
  courses.push_back(new Course("CS102", "Data Structures", 4, 40));
  courses.push_back(new Course("CS103", "Algorithms", 4, 35));
  courses.push_back(new Course("CS104", "UML", 4, 35));
  courses.push_back(new Course("CS108", "Operating Systems", 4, 1));

  printHeader("COURSE REGISTRATION SYSTEM");

  while (true) {
    printOption(1, "Sign Up");
    printOption(2, "Login");
    printOption(3, "Exit");

    cout << "Choose: ";
    int choice;
    cin >> choice;

    if (cin.fail()) {
      clearInput();
      printError("Invalid input!");
      continue;
    }

    if (choice == 1)
      signUp(students);

    else if (choice == 2) {
      string email, pass;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Email: ";
      getline(cin, email);

      if (!isValidEmail(email)) {
        printError("Invalid email format! Please use a valid email (e.g., user@example.com)");
        continue;
      }

      cout << "Password: ";
      getline(cin, pass);

      if (admin.login(email, pass)) {
        adminMenu(admin, courses, students);
        continue;
      }

      Student *logged = findStudent(students, email, pass);
      if (!logged) {
        printError("Invalid login!");
        continue;
      }

      studentMenu(logged, courses);
    }

    else if (choice == 3) {
      printSuccess("Exiting system...");
      break;
    }
  }
}