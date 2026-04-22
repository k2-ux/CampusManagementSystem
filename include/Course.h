#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

class Student;

class Course
{
private:
    std::string name; // ✅ must use std::

    std::vector<Student *> students;

public:
    Course(std::string name); // ✅ must match exactly

    void addStudent(Student *s);

    void display() const;
};

#endif