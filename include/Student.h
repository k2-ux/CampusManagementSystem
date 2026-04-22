#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <vector>

class Student : public Person {
private:
    vector<string> courses; // composition

    static int count; // static variable shared among all objects

public:
    Student(string name, int age);

    void enrollCourse(const string& course);

    void display() const override;

    // operator overloading
    bool operator==(const Student& other) const;
};

#endif