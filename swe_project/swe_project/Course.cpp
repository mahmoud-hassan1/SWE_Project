#include "Course.h"
#include<iostream>
using namespace std;

Course::Course(string code, string name, int hours, int capacity) {
    this->code = code;
    this->name = name;
    this->hours = hours;
    this->capacity = capacity;
    //this->avaliable = true;
    this->numOfRegs = 0;
}
//wa
Course::Course(string code, string name, int hours, int capacity, int reg) {
    this->code = code;
    this->name = name;
    this->hours = hours;
    this->capacity = capacity;
    this->numOfRegs = reg;
    //this->avaliable = false;
}

string Course::getCode() {
    return code;
}

string Course::getName() {
    return name;
}

int Course::getHours() {
    return hours;
}

int Course::getCapacity() {
    return capacity;
}

int Course::getNumOfRegs() {
    return numOfRegs;
}

bool Course::IsAvaliable() {
    return this->capacity != this->numOfRegs;
}

void Course::setName(string name) {
    this->name = name;
}

void Course::setHours(int hours) {
    this->hours = hours;
}

void Course::setCapacity(int capacity) {
    this->capacity = capacity;
}

void Course::updateNumOfRegs(int num) {
    this->numOfRegs = num;
}

void Course::incrementRegister() {
    this->numOfRegs++;
}
