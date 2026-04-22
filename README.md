# Campus Management System

A C++ practice project that demonstrates core object-oriented programming concepts — inheritance, polymorphism, operator overloading, and composition — through a simple command-line interface for managing campus entities like students, professors, courses, and departments.

## Building

```bash
mkdir build && cd build
cmake ..
make
./CampusManagementSystem
```

Requires CMake 3.10+ and a C++17-compatible compiler.

## Project Structure

```
CampusManagementSystem/
├── main.cpp              # Entry point and interactive menu
├── CMakeLists.txt        # Build configuration
├── include/              # Header files
│   ├── Person.h
│   ├── Student.h
│   ├── Professor.h
│   ├── Course.h
│   ├── Department.h
│   └── Utils.h
└── src/                  # Implementation files
    ├── Person.cpp
    ├── Student.cpp
    ├── Professor.cpp
    ├── Course.cpp
    ├── Department.cpp
    └── Utils.cpp
```

## File-by-File Breakdown

### `main.cpp`
The application entry point. Runs a do-while menu loop that lets the user add students and view the student list. Holds three `vector` collections (students, professors, courses), though currently only the student collection is wired into the menu. Wraps execution in a try-catch for standard exceptions.

---

### `include/Person.h` / `src/Person.cpp`
Abstract base class for all campus people. Stores `name` and `age` as protected members. Declares `display()` as a pure virtual method, making `Person` non-instantiable and forcing every derived class to implement its own display logic. Also exposes a `getName()` getter.

---

### `include/Student.h` / `src/Student.cpp`
Derives from `Person`. Adds:
- A `vector<string> courses` list of enrolled course names
- `enrollCourse(const string&)` to add a course
- A `static int count` that increments on each construction, tracking the total number of Student objects created
- `operator==` overload that compares students by name
- A `display()` override that prints name and age

---

### `include/Professor.h` / `src/Professor.cpp`
Derives from `Person`. Adds a `double salary` field and a `display()` override that prints name and salary. Demonstrates the simplest form of inheritance — extending the base with one extra attribute.

---

### `include/Course.h` / `src/Course.cpp`
Represents a course by name and holds a `vector<Student*>` of pointers to enrolled students. Uses a forward declaration of `Student` in the header (with the full include deferred to the `.cpp`) to avoid a circular dependency between `Course` and `Student`. Provides `addStudent(Student*)` and a `display()` method.

---

### `include/Department.h` / `src/Department.cpp`
A container for `Course` objects. Holds a `vector<Course>` and exposes `addCourse(const Course&)` and `display()`, which iterates over all courses and calls their `display()` method. Demonstrates composition at the department level.

---

### `include/Utils.h` / `src/Utils.cpp`
A `Utils` namespace with two file I/O helpers:
- `saveToFile(const string& data)` — writes a string to `data.txt`
- `loadFromFile()` — reads `data.txt` and returns its contents as a single string

These functions exist and work but are not yet called from `main.cpp`.

---

## C++ Concepts Demonstrated

| Concept | Where |
|---|---|
| Abstract classes & pure virtual functions | `Person` |
| Inheritance | `Student`, `Professor` → `Person` |
| Polymorphism | `display()` called through `Person*` |
| Operator overloading | `Student::operator==` |
| Static member variables | `Student::count` |
| Composition | `Department` owns `Course`s; `Course` references `Student`s |
| Forward declaration | `Course.h` forward-declares `Student` |
| Namespaces | `Utils` |
| File I/O | `Utils::saveToFile`, `Utils::loadFromFile` |
| Exception handling | try-catch in `main.cpp` |

## Known Limitations

- The professor and course menus are not yet implemented — only student add/view is hooked up in `main.cpp`.
- `Utils` file I/O is not called anywhere; data does not persist between runs.
- `Course` stores raw `Student*` pointers without managing their lifetime.
