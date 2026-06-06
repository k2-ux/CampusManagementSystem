# Campus Management System - Architecture & Flow Document

## 1. Executive Summary

**What this app does:**
The Campus Management System is a console-based C++ application designed as a structured learning platform for object-oriented programming. Its core purpose is to simulate the administrative operations of a campus — managing students, professors, courses, and departments — through a menu-driven CLI. Users can add student records and view them in-session, while the underlying architecture demonstrates key C++ OOP concepts: abstract base classes, inheritance hierarchies, virtual dispatch (polymorphism), operator overloading, composition, aggregation, static members, and file I/O utilities. The system is intentionally scaffolded as a teaching artefact, with a 50-exercise curriculum (`CURRICULUM.md`) guiding learners from exploration through debugging and refactoring.

The application currently implements a subset of its intended feature set. The data model and class hierarchy are fully defined for Students, Professors, Courses, and Departments, but only the Student add/view flows are wired into the interactive menu. A file-persistence utility (`Utils`) exists but is not yet connected to the runtime. This makes the project ideal as a starting point for learners to extend.

**Tech Stack:**

| Layer | Technology |
|---|---|
| **Language** | C++17 |
| **Build System** | CMake 3.10+ |
| **Compiler Target** | GCC 7+ / Clang 5+ / MSVC 2017+ |
| **Runtime Environment** | Terminal / CLI (stdin/stdout) |
| **Storage** | Flat file (`data.txt`) via `std::fstream` |
| **State Management** | In-memory STL containers (`std::vector`) |
| **Key Standard Library** | `<vector>`, `<string>`, `<fstream>`, `<iostream>` |
| **Design Patterns** | Abstract Base Class, Composition, Aggregation, Operator Overloading |
| **No external dependencies** | Pure standard C++ — no third-party libraries |

---

## 2. High-Level Data Flow

The application follows a **synchronous, single-threaded, request-response loop**. All state lives in-memory for the duration of a session. There is no network layer, no database engine, and no concurrency. Data flow is strictly:

```
User (stdin) → Menu Dispatcher → Domain Object → In-Memory Store → Display (stdout)
```

**Step-by-step for a complete session:**

1. **Program Start** — `main()` initialises three `std::vector` containers on the stack: `students`, `professors`, and `courses`. A `try-catch` block wraps all subsequent logic to catch any `std::exception`.

2. **Menu Render** — The `do-while` loop begins. The menu is printed to `stdout` on every iteration, prompting the user for an integer choice via `cin >> choice`.

3. **Dispatch** — A `switch` statement routes `choice` to the appropriate handler. Currently only cases `1` (Add Student) and `2` (View Students) are implemented; `3` exits the loop. Any unrecognised input falls through silently.

4. **Data Entry (Case 1)** — The user provides a `name` (string) and `age` (int) via `cin`. A `Student` object is constructed in-place at the back of the `students` vector using `emplace_back(name, age)`. During construction, the `Student` constructor calls the `Person` base constructor (via initializer list) and increments the shared static counter `Student::count`.

5. **Data Display (Case 2)** — A range-based `for` loop iterates over the `students` vector. For each `Student`, the virtual method `display()` is dispatched at runtime via C++'s vtable mechanism. Because `Student` overrides `Person::display()`, the student-specific format ("Student: \<name\> Age: \<age\>") is printed to `stdout`.

6. **Persistence Gap** — On exit (Case 3), the loop terminates and `main()` returns. The `students`, `professors`, and `courses` vectors are destroyed; **all data is lost**. The `Utils::saveToFile()` function exists and is capable of writing a string to `data.txt`, but it is not called anywhere in the current codebase.

7. **Error Path** — If any `std::exception` is thrown during execution (e.g., memory allocation failure), the outer `catch` block intercepts it and prints `e.what()` to `stdout`, then the program terminates.

```
┌─────────────────────────────────────────────────────┐
│                     main()                           │
│  ┌──────────────────────────────────────────────┐   │
│  │  try {                                        │   │
│  │    vector<Student>   students                 │   │
│  │    vector<Professor> professors   (unused)    │   │
│  │    vector<Course>    courses      (unused)    │   │
│  │                                               │   │
│  │    do {                                       │   │
│  │      print menu → cin >> choice               │   │
│  │      switch(choice):                          │   │
│  │        case 1 → cin name/age                  │   │
│  │                 students.emplace_back(n,a)    │   │
│  │                   └─ Student(n,a)             │   │
│  │                       └─ Person(n,a)          │   │
│  │                       └─ Student::count++     │   │
│  │        case 2 → for s in students:            │   │
│  │                   s.display()  [virtual]      │   │
│  │                     └─ Student::display()     │   │
│  │        case 3 → exit loop                     │   │
│  │    } while(choice != 3)                       │   │
│  │  } catch(exception& e) { cout e.what() }     │   │
│  └──────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────┘
                         │
              (data lost on exit)
                         │
            ┌────────────▼────────────┐
            │  data.txt  (Utils only) │   ← NOT connected
            └─────────────────────────┘
```

---

## 3. Core Modules Breakdown

---

### Module: Person (Abstract Base Layer)

**Responsibility:** Defines the shared contract for all human entities in the system. Enforces that every concrete entity must implement a `display()` method. Owns the common data fields (`name`, `age`) and provides safe polymorphic destruction.

**Key Files:**
- `include/Person.h` — Declares the abstract class with pure virtual `display()`
- `src/Person.cpp` — Implements the constructor using an initializer list; defines the virtual destructor body

**How it works:**
`Person` is non-instantiable because `display()` is declared `= 0` (pure virtual). Any class inheriting from `Person` must override `display()` or it also becomes abstract. The virtual destructor (`virtual ~Person()`) ensures that when a `Student` or `Professor` is deleted through a `Person*`, the derived class destructor is called first — preventing resource leaks. The `getName()` accessor provides read-only access to the protected `name` field.

```
Person (abstract)
├── protected: string name, int age
├── Person(string, int)        ← initializer list
├── virtual ~Person()          ← enables safe polymorphic delete
├── virtual display() = 0      ← pure virtual: forces override
└── getName() const            ← accessor
```

---

### Module: Student (Entity + Enrollment)

**Responsibility:** Represents a student, tracks course enrollment by name, and maintains a program-wide count of all student instances created.

**Key Files:**
- `include/Student.h` — Class declaration with `vector<string> courses` and `static int count`
- `src/Student.cpp` — Implements constructor, `enrollCourse()`, `display()`, `operator==`, and defines the static member

**How it works:**
The `Student` constructor calls `Person(name, age)` via the initializer list and increments `Student::count` (a static integer shared across all instances, defined once in `Student.cpp`). `enrollCourse()` pushes a course name (string) into the private `courses` vector. `operator==` compares two students by `name`, which enables use of `std::find` or similar algorithms. `display()` overrides the pure virtual method from `Person`, outputting "Student: \<name\> Age: \<age\>".

```
Student : public Person
├── private: vector<string> courses
├── private: static int count       ← shared across all instances
├── Student(name, age)              ← calls Person(name,age) + count++
├── enrollCourse(string)            ← push_back to courses vector
├── display() const override        ← fulfills pure virtual contract
└── operator==(Student&) const      ← name-based equality
```

---

### Module: Professor (Entity)

**Responsibility:** Represents a professor with salary information. Demonstrates how to extend the `Person` base class with domain-specific attributes.

**Key Files:**
- `include/Professor.h` — Declares `double salary` and constructor
- `src/Professor.cpp` — Implements constructor and `display()`

**How it works:**
The `Professor` constructor receives `name`, `age`, and `salary`, forwarding the first two to `Person` via the initializer list and storing `salary` as a private member. `display()` overrides `Person`'s pure virtual method, printing "Professor: \<name\> Salary: \<salary\>". The module is currently declared and instantiated in `main.cpp` but no menu cases route into it.

```
Professor : public Person
├── private: double salary
├── Professor(name, age, salary)    ← calls Person(name,age)
└── display() const override        ← "Professor: X Salary: Y"
```

---

### Module: Course (Enrollment Aggregator)

**Responsibility:** Represents a course and holds pointers to enrolled `Student` objects. Demonstrates aggregation (owns references, not the students themselves) and forward-declaration to resolve circular dependencies.

**Key Files:**
- `include/Course.h` — Forward-declares `class Student;`, stores `vector<Student*>`
- `src/Course.cpp` — Includes `Student.h` for the full type definition; implements `addStudent()` and `display()`

**How it works:**
Because `Student` and `Course` mutually reference each other (a student enrolls in courses; a course contains students), `Course.h` uses a forward declaration (`class Student;`) rather than `#include "Student.h"`. This breaks the circular include chain. `Course.cpp` then includes `Student.h` where the full type is needed. `addStudent()` appends a raw `Student*` to the `students` vector. **Known issue:** raw pointer storage without ownership semantics means if a `Student` object is destroyed while still referenced by a `Course`, accessing that pointer is undefined behaviour (dangling pointer / segfault).

```
Course
├── private: string name
├── private: vector<Student*> students   ← aggregation (not ownership)
├── Course(string name)
├── addStudent(Student*)                 ← appends raw pointer (risky)
└── display() const                      ← prints course name only
```

---

### Module: Department (Structural Container)

**Responsibility:** Acts as a top-level organisational container that owns a collection of `Course` objects. Demonstrates the composition pattern — a Department is meaningless without its courses.

**Key Files:**
- `include/Department.h` — Stores `vector<Course>` by value
- `src/Department.cpp` — Implements `addCourse()` and `display()`

**How it works:**
`addCourse()` takes a `Course` by const reference and copies it into the internal vector (value semantics). `display()` iterates the vector and calls `course.display()` on each element. Because `Course` objects are stored by value, `Department` owns their lifetime — if the `Department` is destroyed, all its `Course` objects are destroyed too. This is classic composition.

```
Department
├── private: vector<Course> courses     ← composition (owns courses)
├── addCourse(const Course&)            ← copies course into vector
└── display() const                      ← delegates to Course::display()
```

---

### Module: Utils (File Persistence Layer)

**Responsibility:** Provides the only I/O bridge between the in-memory application state and durable flat-file storage (`data.txt`). Currently unused by the rest of the application.

**Key Files:**
- `include/Utils.h` — Declares the `Utils` namespace with two function signatures
- `src/Utils.cpp` — Implements `saveToFile()` and `loadFromFile()` using `std::ofstream` / `std::ifstream`

**How it works:**
`saveToFile(const std::string& data)` opens `data.txt` in write mode (truncating any existing content) and writes the provided string. `loadFromFile()` opens `data.txt` in read mode, iterates lines with `std::getline()`, concatenates them into a single return string, and closes the file. Neither function performs error checking (file not found, permission denied, or write failure). Since neither function is called in `main.cpp`, all session data is volatile.

```
namespace Utils
├── saveToFile(string data)    ← ofstream → "data.txt" (truncate write)
└── loadFromFile() → string    ← ifstream → reads "data.txt" line by line
                                 (no error handling; not called anywhere)
```

---

### Module: Application Shell (main.cpp)

**Responsibility:** Owns the application lifecycle — initialises all in-memory stores, runs the interactive event loop, dispatches user input to the correct domain module, and handles top-level exceptions.

**Key Files:**
- `main.cpp` — Single file; all runtime orchestration

**How it works:**
Three STL vectors serve as the in-memory "database." A `do-while` loop acts as the event loop, rendering the menu and blocking on `cin`. A `switch` statement routes the user's integer choice to the correct handler. A `try-catch(std::exception&)` wraps the entire loop body, providing a last-resort error boundary. Student construction uses `emplace_back` (constructs in place, avoiding an extra copy). The professors and courses vectors are declared but never touched by the menu.

---

## 4. User Flows & Use Cases

---

### Flow: Add Student

**Happy Path:**
1. Program displays the main menu.
2. User enters `1` and presses Enter.
3. Program prints "Enter name: " — user types a single-word name (e.g., `Alice`) and presses Enter.
4. Program prints "Enter age: " — user types an integer (e.g., `20`) and presses Enter.
5. `students.emplace_back("Alice", 20)` is called.
   - `Student` constructor fires → `Person("Alice", 20)` initializes `name` and `age` via initializer list → `Student::count` increments to 1.
6. Control returns to the top of the `do-while` loop; the menu is reprinted.

**Edge Cases & Error Handling:**

| Scenario | What Happens |
|---|---|
| **Name with spaces** (e.g., `John Doe`) | `cin >> name` reads only `John`; `Doe` remains in the input buffer and is consumed as the age input on the next `cin >> age`, causing `age` to fail to parse. The student may be created with `name = "John"` and age = 0 (or undefined behaviour depending on stream state). No error is shown to the user. |
| **Non-integer age** (e.g., `twenty`) | `cin >> age` fails, leaving the stream in a fail state. The menu re-renders but subsequent `cin` reads will silently fail until the error state is cleared. No recovery logic exists. |
| **Negative or implausible age** (e.g., `-5` or `999`) | Accepted without validation. The `Student` object is created with the given age. No range check exists in the current code. |
| **Empty name** (just pressing Enter) | `cin >>` skips whitespace, so an empty input causes `cin` to block until a non-whitespace token is entered. No explicit empty-string guard exists. |
| **Memory exhaustion** | `vector::emplace_back` may throw `std::bad_alloc`. This is caught by the outer `catch(std::exception& e)` block, which prints `e.what()` and terminates the loop. |

---

### Flow: View Students

**Happy Path:**
1. User enters `2` at the main menu.
2. A range-based `for` loop iterates over the `students` vector.
3. For each `Student s`, `s.display()` is called.
   - The vtable resolves this to `Student::display()` at runtime.
   - Output: `Student: Alice Age: 20`
4. After all students are printed, the menu loop resumes.

**Edge Cases & Error Handling:**

| Scenario | What Happens |
|---|---|
| **No students added yet** | The `for` loop body never executes. No output is produced and no "empty list" message is shown. The menu re-renders silently. |
| **Large number of students** | All entries are printed sequentially with no pagination. The terminal scrolls. No performance issue at typical interactive scale. |

---

### Flow: Exit Application

**Happy Path:**
1. User enters `3` at the main menu.
2. The `while(choice != 3)` condition is evaluated; it is false.
3. The `do-while` loop exits.
4. `main()` returns `0`; all stack-allocated vectors (`students`, `professors`, `courses`) are destroyed — their destructors deallocate heap memory held by the vectors.
5. Because `Student` and `Professor` destructors are handled through the virtual destructor chain (`~Person()` is virtual), all polymorphic objects are cleanly destroyed.
6. **Data loss:** All added students are gone. There is no save-on-exit call to `Utils::saveToFile()`.

**Edge Cases & Error Handling:**

| Scenario | What Happens |
|---|---|
| **Invalid menu choice** (e.g., `5`, `-1`) | The `switch` statement has no `default` case. The loop continues silently to the next iteration and reprints the menu. No feedback is given. |
| **Non-integer menu input** (e.g., `abc`) | `cin >> choice` fails; `choice` retains its previous value. The stream enters a fail state. The loop may spin indefinitely reprinting the menu. No recovery logic exists. |
| **Ctrl+C / signal interrupt** | The OS terminates the process. Stack unwinding occurs, and destructors are called on local variables, cleaning up memory. No data is saved. |
| **`std::exception` thrown** | The outer `catch` prints `e.what()` and falls through to the end of `main()`, returning `0`. The menu loop does not resume. |

---

### Flow: Persist / Reload Data (Designed but Not Connected)

**Intended Happy Path** (based on `Utils` module — not yet implemented in `main.cpp`):
1. After adding students, user selects a "Save" option (not in current menu).
2. Application serialises student data into a string and calls `Utils::saveToFile(data)`.
3. `ofstream` opens `data.txt` in write mode, writes the string, and closes.
4. On next program launch, application calls `Utils::loadFromFile()`.
5. `ifstream` opens `data.txt`, reads lines, and the application deserialises them back into `Student` objects.

**Edge Cases & Error Handling (current Utils code):**

| Scenario | What Happens |
|---|---|
| **`data.txt` does not exist on load** | `ifstream` opens unsuccessfully. The `while(getline(...))` loop never executes. An empty string is returned. No error is thrown or logged — silent failure. |
| **No write permission on `data.txt`** | `ofstream` fails to open. The write is silently skipped. No error checking exists. |
| **File partially written (crash mid-save)** | `data.txt` contains truncated data. On next load, partial data is returned and parsed with no validation. |
| **Newline stripping** | `loadFromFile()` reads line-by-line and concatenates without re-inserting newlines, collapsing multi-line content into a single string. Deserialization would need to account for this. |

---

### Flow: Enroll Student in Course (Designed but Not Connected to Menu)

**Intended Happy Path** (based on `Student::enrollCourse()` and `Course::addStudent()`):
1. A `Course` object (e.g., `CS101`) is created.
2. `Student::enrollCourse("CS101")` adds the course name string to the student's internal `courses` vector.
3. Separately, `Course::addStudent(&student)` adds a raw pointer to the student into the course's `students` vector.

**Edge Cases & Error Handling:**

| Scenario | What Happens |
|---|---|
| **Student enrolled twice** | `enrollCourse()` has no duplicate check — the same course name is appended twice to `courses`. No guard exists. |
| **Student object moved/destroyed after `addStudent()`** | The raw `Student*` stored in `Course::students` becomes a dangling pointer. Any subsequent call to `Course::display()` (if it iterated students) would be undefined behaviour. **This is the most critical bug in the codebase.** |
| **Course added to Department, then student enrolled** | The `Department` stores `Course` by value (copy). If a student pointer is added to the original `Course` object after it was copied into `Department`, the copy inside `Department::courses` does not reflect the update. |

---

*Document generated from static analysis of the full source tree at commit `36ce5d2` (Initial commit: Campus Management System). Code line counts and behaviour verified against: `main.cpp`, `include/*.h`, `src/*.cpp`, `CMakeLists.txt`, `README.md`, `CURRICULUM.md`.*
