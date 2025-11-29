#include <iostream>
#include <vector>
#include <limits>
using namespace std;

#include "Admin.h"
#include "Student.h"
#include "Course.h"
#include "Account.h"

// ================================
// ANSI COLORS
// ================================
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"

// ================================
// UTILITY FUNCTIONS
// ================================
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void line() {
    cout << CYAN << "----------------------------------------" << RESET << "\n";
}

// ================================
// UI FUNCTIONS
// ================================
void printHeader(const string& title) {
    cout << BLUE << BOLD
        << "\n========================================\n"
        << "         " << title << "\n"
        << "========================================\n"
        << RESET;
}

void printSuccess(const string& msg) {
    cout << GREEN << "[✔] " << msg << RESET << "\n";
}

void printError(const string& msg) {
    cout << RED << "[✘] " << msg << RESET << "\n";
}

void printOption(int num, const string& text) {
    cout << YELLOW << num << ". " << RESET << text << "\n";
}

// ================================
// SEARCH HELPERS
// ================================
Student* findStudent(vector<Student*>& students, const string& email, const string& pass) {
    for (auto s : students)
        if (s->login(email, pass))
            return s;
    return nullptr;
}

Course* findCourse(vector<Course*>& courses, const string& code) {
    for (auto c : courses)
        if (c->getCode() == code)
            return c;
    return nullptr;
}

// ================================
// SIGN UP FUNCTION
// ================================
void signUp(vector<Student*>& students) {
    printHeader("SIGN UP");

    string name, email, pass;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover input
    cout << "Enter your name: ";
    getline(cin, name); // allows spaces

    cout << "Enter your email: ";
    getline(cin, email);

    cout << "Enter password: ";
    getline(cin, pass);

    students.push_back(new Student(name, email, pass));

    printSuccess("Account created successfully!");
}


// ================================
// ADMIN MENUS
// ================================
void adminMenu(Admin& admin, vector<Course*>& courses) {
    printHeader("ADMIN PANEL");

    while (true) {
        printOption(1, "Create Course");
        printOption(2, "Edit Course");
        printOption(3, "Delete Course");
        printOption(4, "Show All Courses");
        printOption(5, "Logout");

        cout << CYAN << "Choose: " << RESET;
        int c;
        cin >> c;

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
            cin >> name;
            cout << "Enter hours: ";
            cin >> hours;
            cout << "Enter capacity: ";
            cin >> cap;

            courses.push_back(admin.createCourse(code, name, hours, cap));
            printSuccess("Course created!");
        }

        else if (c == 2) {
            string code;
            cout << "Enter course code to edit: ";
            cin >> code;

            Course* target = findCourse(courses, code);
            if (!target) {
                printError("Course not found!");
                continue;
            }

            string name;
            int hours, cap;
            cout << "Enter new name: ";
            cin >> name;
            cout << "Enter new hours: ";
            cin >> hours;
            cout << "Enter new capacity: ";
            cin >> cap;

            admin.editCourse(target, name, hours, cap);
            printSuccess("Course updated!");
        }

        else if (c == 3) {
            string code;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter course code to delete: ";
            getline(cin, code);

            if (admin.deleteCourse(courses, code))
                printSuccess("Course deleted!");
            else
                printError("Course not found!");
        }

        else if (c == 4) {
            printHeader("ALL COURSES");

            for (auto c : courses) {
                cout << CYAN << c->getCode() << RESET
                    << " | " << c->getName()
                    << " | " << c->getHours() << "h"
                    << " | Cap: " << c->getCapacity()
                    << " | Regs: " << c->getNumOfRegs()
                    << " | Available: " << boolalpha << c->IsAvaliable()
                    << "\n";
            }
        }

        else if (c == 5) {
            printSuccess("Logged out.");
            break;
        }
    }
}

// ================================
// STUDENT MENUS
// ================================
void studentMenu(Student* logged, vector<Course*>& courses) {
    printHeader("STUDENT PANEL");

    while (true) {
        printOption(1, "Register Course");
        printOption(2, "Drop Course");
        printOption(3, "Show My Courses");
        printOption(4, "Show Available Courses");
        printOption(5, "Logout");

        cout << CYAN << "Choose: " << RESET;
        int c;
        cin >> c;

        // ===========================
        // REGISTER COURSE
        // ===========================
        if (c == 1) {
            string code;
            cout << "Enter course code: ";
            cin >> code;

            // find course in course list
            Course* target = nullptr;
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

            // check if student is already registered
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

        // ===========================
        // DROP COURSE
        // ===========================
        else if (c == 2) {
            string code;
            cout << "Enter course code to drop: ";
            cin >> code;

            Course* target = nullptr;

            // find course in the student's registered courses
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

        // ===========================
        // SHOW STUDENT COURSES
        // ===========================
        else if (c == 3) {
            printHeader("MY COURSES");
            logged->showCourse();
        }

        // ===========================
        // SHOW AVAILABLE COURSES
        // ===========================
        else if (c == 4) {
            printHeader("AVAILABLE COURSES");

            for (auto c : courses) {
                if (c->IsAvaliable()) {
                    cout << c->getCode() << " - " << c->getName()
                        <<" (hours: "<<c->getHours()<<"\tCapacity: " << c->getCapacity() << "\tRegs: " << c->getNumOfRegs() << ")\n";
                }
            }
        }

        // ===========================
        // EXIT
        // ===========================
        else if (c == 5) {
            printSuccess("Logged out.");
            break;
        }
    }
}


// ================================
// MAIN FUNCTION
// ================================
int main()
{
    Admin admin("Admin", "admin@system.com", "123");
    vector<Student*> students;
    vector<Course*> courses;

    // Predefined Courses
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

        cout << CYAN << "Choose: " << RESET;
        int choice;
        cin >> choice;

        if (choice == 1)
            signUp(students);

        else if (choice == 2) {
            string email, pass;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover input
            cout << "Email: ";
            getline(cin, email);

            cout << "Password: ";
            getline(cin, pass);

            // Admin Login
            if (admin.login(email, pass)) {
                adminMenu(admin, courses);
                continue;
            }

            // Student Login
            Student* logged = findStudent(students, email, pass);
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
