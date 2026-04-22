#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "Person.h"

class Professor : public Person {
private:
    double salary;

public:
    Professor(string name, int age, double salary);

    void display() const override;
};

#endif