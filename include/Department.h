#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "Course.h"
#include <vector>

class Department {
private:
    std::vector<Course> courses;

public:
    void addCourse(const Course& c);
    void display() const;
};

#endif