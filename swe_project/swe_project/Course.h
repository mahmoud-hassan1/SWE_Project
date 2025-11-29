#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;
class Course {
private:
    string code;
    string name;
    int hours;
    int capacity;
    int numOfRegs;

public:
    Course(string code,string name, int hours, int capacity);
    //wa
    Course(string code,string name, int hours, int capacity, int numOfRegs );

    string getCode();
    string getName();
    int getHours();
    int getCapacity();
    int getNumOfRegs();
    bool IsAvaliable();

    void setName(string name);
    void setHours(int hours);
    void setCapacity(int capacity);
    void updateNumOfRegs(int num);
    void incrementRegister();
};


#endif