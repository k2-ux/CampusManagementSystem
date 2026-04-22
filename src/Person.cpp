#include "Person.h"

// Constructor
Person::Person(string name, int age) : name(name), age(age) {}

// Destructor
Person::~Person() {}

string Person::getName() const {
    return name;
}