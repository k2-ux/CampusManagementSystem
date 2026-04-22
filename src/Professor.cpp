#include "Professor.h"
#include <iostream>

Professor::Professor(string name, int age, double salary)
    : Person(name, age), salary(salary) {}

void Professor::display() const {
    std::cout << "Professor: " << name << " Salary: " << salary << std::endl;
}