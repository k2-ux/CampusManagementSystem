#include "Course.h"
#include "Student.h"
#include <iostream>

Course::Course(std::string name) : name(name) {}

void Course::addStudent(Student *s)
{
    students.push_back(s);
}

void Course::display() const
{
    std::cout << "Course: " << name << std::endl;
}