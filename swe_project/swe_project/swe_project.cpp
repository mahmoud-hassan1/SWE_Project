#include <iostream>
#include <vector>
#include <limits>
using namespace std;

#include "Admin.h"
#include "Student.h"
#include "Course.h"
#include "Account.h"

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    // -----------------------
    // 1. CONSTANT ADMIN
    // -----------------------
    Admin admin("Admin", "admin@system.com", "123");

    // -----------------------
    // 2. LIST OF ACCOUNTS
    // -----------------------
    vector<Student*> students;

    // -----------------------
    // 3. PREDEFINED COURSES
    // -----------------------
    vector<Course*> courses;
    courses.push_back(new Course("CS101", "Intro to CS", 3, 50));
    courses.push_back(new Course("CS102", "Data Structures", 4, 40));
    courses.push_back(new Course("CS103", "Algorithms", 4, 35));

    cout << "=============================\n";
    cout << "  COURSE REGISTRATION SYSTEM \n";
    cout << "=============================\n";

    while (true) {
        cout << "\n1. Sign Up\n2. Login\n3. Exit\nChoose: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            // -----------------------
            // SIGN UP
            // -----------------------
            string name, email, pass;

            cout << "Enter name: ";
            cin >> name;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            cin >> pass;

            students.push_back(new Student(name, email, pass));
            cout << "Account created successfully!\n";
        }

        else if (choice == 2) {
            // -----------------------
            // LOGIN
            // -----------------------
            string email, pass;
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter password: ";
            cin >> pass;

            // Admin login
            if (admin.login(email, pass)) {
                cout << "\n=== Logged in as ADMIN ===\n";

                while (true) {
                    cout << "\n1. Create Course\n2. Edit Course\n3. Delete Course\n4. Show All Courses\n5. Logout\nChoose: ";
                    int c;
                    cin >> c;

                    if (c == 1) {
                        // CREATE COURSE
                        string code, name;
                        int hours, cap;

                        cout << "Enter course code: ";
                        cin >> code;
                        bool flag = false;
                        for (auto c : courses)
                        {
                            if (c->getCode() == code) {
                                cout << "This Code Is Already Existed\n";
                                flag = true;
                            }

                        }
                        if (flag)
                            continue;
                        cout << "Enter course name: ";
                        cin >> name;
                        cout << "Enter hours: ";
                        cin >> hours;
                        cout << "Enter capacity: ";
                        cin >> cap;

                        courses.push_back(admin.createCourse(code, name, hours, cap));
                        cout << "Course created!\n";
                    }

                    else if (c == 2) {
                        // EDIT COURSE
                        string code;
                        cout << "Enter course code to edit: ";
                        cin >> code;

                        Course* target = nullptr;
                        for (auto c : courses)
                            if (c->getCode() == code)
                                target = c;

                        if (!target) {
                            cout << "Course not found!\n";
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
                        cout << "Course updated!\n";
                    }

                    else if (c == 3) {
                        // DELETE COURSE
                        string code;
                        cout << "Enter course code to delete: ";
                        cin >> code;

                        for (int i = 0; i < courses.size(); i++) {
                            if (courses[i]->getCode() == code) {
                                admin.deleteCourse(courses[i]);
                                cout << "Course deleted!\n";
                                courses.erase(courses.begin() + i);
                                break;
                            }
                        }
                    }

                    else if (c == 4) {
                        // SHOW ALL COURSES
                        cout << "\n=== Available Courses ===\n";
                        for (auto c : courses) {
                            cout << c->getCode() << " | "
                                << c->getName() << " | "
                                << c->getHours() << "h | Cap: "
                                << c->getCapacity() << " | Regs: "
                                << c->getNumOfRegs() << "\n";
                        }
                    }

                    else if (c == 5)
                        break;
                }
            }

            // Student login
            else {
                Student* logged = nullptr;
                for (auto s : students)
                    if (s->login(email, pass))
                        logged = s;

                if (!logged) {
                    cout << "Invalid login!\n";
                    continue;
                }

                cout << "\n=== Logged in as STUDENT ===\n";

                while (true) {
                    cout << "\n1. Register Course\n2. Drop Course\n3. Show My Courses\n4. Show All Courses\n5. Logout\nChoose: ";
                    int c;
                    cin >> c;

                    if (c == 1) {
                        string code;
                        cout << "Enter course code: ";
                        cin >> code;

                        Course* target = nullptr;
                        for (auto c : courses)
                            if (c->getCode() == code)
                                target = c;

                        if (!target) {
                            cout << "Course not found!\n";
                            continue;
                        }
                        auto studcourses = logged->getCourses();
                        bool flag = false;
                        for (auto c : studcourses)
                        {
                            if (code == c->getCode())
                            {
                                flag = true;
                                break;
                            }
                        }
                        if (flag) {
                            cout << "You Already Registred This Course \n";
                            continue;
                        }

                        logged->regCourse(target);
                        cout << "Course registered!\n";
                    }

                    else if (c == 2) {
                        string code;
                        cout << "Enter course code to drop: ";
                        cin >> code;

                        Course* target = nullptr;
                        for (auto c : logged->getCourses())
                            if (c->getCode() == code)
                                target = c;

                        if (!target) {
                            cout << "You are not registered in this course!\n";
                            continue;
                        }

                        logged->dropCourse(target);
                        cout << "Course dropped!\n";
                    }

                    else if (c == 3) {
                        logged->showCourse();
                    }

                    else if (c == 4) {
                        cout << "\n=== Available Courses ===\n";
                        for (auto c : courses) {
                            cout << c->getCode() << " | "
                                << c->getName() << " | "
                                << c->getHours() << " hours | Capacity: "
                                << c->getCapacity() << " | Regs: "
                                << c->getNumOfRegs() << "\n";
                        }
                    }

                    else if (c == 5)
                        break;
                }
            }
        }

        else if (choice == 3) {
            cout << "Exiting system...\n";
            break;
        }
    }

    return 0;
}
