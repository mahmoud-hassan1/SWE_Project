#include "LoginInterface.h"
#include <iostream>

using namespace std;

bool LoginInterface::isValidEmail(string email) {
    int atPos = -1;
    int dotPos = -1;
    
    for (int i = 0; i < email.length(); i++) {
        if (email[i] == '@') {
            if (atPos != -1) {
                return false;
            }
            atPos = i;
        }
        if (email[i] == '.' && atPos != -1) {
            dotPos = i;
        }
    }
    
    if (atPos < 1) {
        return false;
    }
    if (dotPos <= atPos + 1) {
        return false;
    }
    if (dotPos >= email.length() - 1) {
        return false;
    }
    
    return true;
}

LoginInterface::LoginInterface(System* system, RegistrationController* regController,
                               AdminController* adminController, StudentInterface* studentInterface,
                               AdminInterface* adminInterface) {
    this->system = system;
    this->regController = regController;
    this->adminController = adminController;
    this->studentInterface = studentInterface;
    this->adminInterface = adminInterface;
}

void LoginInterface::displayMenu() {
    int choice;
    
    while (true) {
        cout << "\n========== Course Registration System ==========" << endl;
        cout << "1. Login" << endl;
        cout << "2. Signup" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                handleLogin();
                break;
            case 2:
                handleSignup();
                break;
            case 3:
                cout << "Goodbye!" << endl;
                return;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

void LoginInterface::handleLogin() {
    string email;
    string password;
    int userType;
    
    cout << "\n========== Login ==========" << endl;
    cout << "1. Student" << endl;
    cout << "2. Admin" << endl;
    cout << "Select user type: ";
    cin >> userType;
    
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;
    
    if (userType == 1) {
        Student* student = regController->requestAuthentication(email, password);
        if (student != nullptr) {
            cout << "Login Successful! Welcome " << student->getName() << endl;
            studentInterface->setCurrentStudent(student);
            studentInterface->displayMainMenu();
        } else {
            cout << "Login Failed! Invalid credentials." << endl;
        }
    } else if (userType == 2) {
        Admin* admin = adminController->requestAuthentication(email, password);
        if (admin != nullptr) {
            cout << "Login Successful! Welcome " << admin->getName() << endl;
            adminInterface->setCurrentAdmin(admin);
            adminInterface->displayMainMenu();
        } else {
            cout << "Login Failed! Invalid credentials." << endl;
        }
    } else {
        cout << "Invalid user type." << endl;
    }
}

void LoginInterface::handleSignup() {
    string name;
    string email;
    string password;
    
    cout << "\n========== Student Signup ==========" << endl;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;
    
    if (!isValidEmail(email)) {
        cout << "Registration Failed! Invalid email format." << endl;
        return;
    }
    
    if (system->emailExists(email)) {
        cout << "Registration Failed! Email already exists." << endl;
        return;
    }
    
    Student* student = new Student(name, email, password);
    system->addStudent(student);
    cout << "Registration Complete! You can now login." << endl;
}
