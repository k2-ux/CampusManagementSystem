#include "Student.h"
#include <iostream>

int Student::count = 0;

Student::Student(string name, int age)
    : Person(name, age) {
    count++;
}

void Student::enrollCourse(const string& course) {
    courses.push_back(course);
}

void Student::display() const {
    std::cout << "Student: " << name << " Age: " << age << std::endl;
}

bool Student::operator==(const Student& other) const {
    return this->name == other.name;
}

// STUDY EXERCISE:
// Add a function to remove a course from student