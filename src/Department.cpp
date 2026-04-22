#include "Department.h"
#include <iostream>

void Department::addCourse(const Course& c) {
    courses.push_back(c);
}

void Department::display() const {
    for (const auto& c : courses) {
        c.display();
    }
}