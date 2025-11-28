#ifndef SYSTEM_H
#define SYSTEM_H

#include "../models/Student.h"
#include "../models/Admin.h"
#include "../models/Course.h"
#include <vector>
#include <string>

class System {
private:
    std::vector<Student*> students;
    std::vector<Admin*> admins;
    std::vector<Course*> courses;
    int courseCodeCounter;

public:
    System();
    ~System();
    
    Student* findStudent(std::string email, std::string password);
    Admin* findAdmin(std::string email, std::string password);
    bool emailExists(std::string email);
    
    void addStudent(Student* student);
    void addAdmin(Admin* admin);
    void addCourse(Course* course);
    void removeCourse(Course* course);
    
    std::vector<Course*>& getCourses();
    Course* findCourseByCode(std::string code);
    bool courseNameExists(std::string name);
    std::string generateCourseCode();
};

#endif
