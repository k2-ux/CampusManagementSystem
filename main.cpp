#include <iostream>
#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include "Department.h"
#include "Utils.h"

using namespace std;

int main() {
    try {
        // VECTOR = dynamic array
        vector<Student> students;
        vector<Professor> professors;
        vector<Course> courses;

        int choice;

        do {
            cout << "\n--- Campus Management System ---\n";
            cout << "1. Add Student\n2. View Students\n3. Exit\n";
            cin >> choice;

            switch(choice) {
                case 1: {
                    string name;
                    int age;

                    cout << "Enter name: ";
                    cin >> name;

                    cout << "Enter age: ";
                    cin >> age;

                    students.emplace_back(name, age); // constructor call
                    break;
                }
                case 2:
                    for (const auto& s : students) {
                        s.display(); // polymorphism later
                    }
                    break;
            }
        } while(choice != 3);

    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}