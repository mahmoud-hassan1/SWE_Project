#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
private:
    std::string code;
    std::string name;
    int hours;
    int capacity;
    int numOfRegs;

public:
    Course(std::string code, std::string name, int hours, int capacity);
    
    std::string getCode();
    std::string getName();
    int getHours();
    int getCapacity();
    int getNumOfRegs();
    
    void setName(std::string name);
    void setHours(int hours);
    void setCapacity(int capacity);
    void updateNumOfRegs(int num);
};

#endif
