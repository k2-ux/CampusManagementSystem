#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

// ABSTRACT CLASS (cannot create object directly)
class Person {
protected:
    string name;
    int age;

public:
    // Constructor
    Person(string name, int age);

    // Virtual destructor (important for inheritance)
    virtual ~Person();

    // Pure virtual function → forces derived classes to implement
    virtual void display() const = 0;

    string getName() const;
};

#endif