# Campus Management System — Learning Curriculum

**50 progressive micro-exercises to take you from beginner to confident contributor.**

Each task names the exact file(s) to open. No solutions are provided — work through each one yourself.

---

## Phase 1: Exploration & Tracing (Tasks 1–10)

> Goal: Read code, follow data flow, and add debug output to build a mental model of the system.

- [ ] **1. Build the project from scratch.**
  Open `CMakeLists.txt` and read every line. Then build the project:
  ```
  mkdir build && cd build && cmake .. && make
  ```
  After a successful build, add a comment block at the very top of `main.cpp` listing: the C++ standard version, the executable name, and the include path — all sourced from `CMakeLists.txt`.

- [ ] **2. Map the `Person` base class.**
  Open `include/Person.h` and `src/Person.cpp`. Identify: the pure virtual function, the two protected data members, and the virtual destructor. Add a short inline comment next to each of those three things explaining in your own words why each one exists.

- [ ] **3. Trace the static student counter.**
  Open `include/Student.h` and `src/Student.cpp`. Find the `static int count` member and the constructor. Add a `std::cout` line inside the `Student` constructor that prints:
  ```
  [DEBUG] Student created. Total count: <count>
  ```
  Build, run the program, add two students via the menu, and verify the counter increments correctly.

- [ ] **4. Flowchart the main menu loop.**
  Open `main.cpp` and read the entire `while` loop and every `case` branch. On paper or in a plain `.txt` file, draw a flowchart that traces the exact code path for: entering `1` (add student), then `2` (view students), then `5` (exit). Note which variables are modified at each step.

- [ ] **5. Trace `enrollCourse` execution.**
  Open `src/Student.cpp` and find the `enrollCourse` method. Add a `std::cout` debug line inside it that prints:
  ```
  [DEBUG] Enrolling student <name> in course <courseName>
  ```
  Then temporarily add code in `main.cpp` to create one `Student` and one `Course` object and call `enrollCourse`. Build, run, and verify the message appears.

- [ ] **6. Understand the forward declaration.**
  Open `include/Course.h`. Find the forward declaration of `Student` at the top. Now open `include/Student.h` — notice it includes `Course.h`. Write a comment in `Course.h` above the forward declaration explaining in your own words: why a forward declaration is used here instead of `#include "Student.h"`, and what problem that would cause.

- [ ] **7. Trace `Department`'s display chain.**
  Open `include/Department.h`, `src/Department.cpp`, `src/Course.cpp`, and `src/Student.cpp`. Starting from `Department::display()`, trace the full call chain down to what eventually gets printed to the console for a single student. Write the chain as a comment at the top of `src/Department.cpp` (e.g., `Department::display → Course::display → Student::display`).

- [ ] **8. Audit the incomplete menu.**
  Open `main.cpp`. The menu prints options for professors and courses, but most cases do nothing. Add a `std::cout` line inside each empty/unimplemented `case` that prints:
  ```
  [TODO] This feature is not yet implemented.
  ```
  Build and run the program. Test every menu option and confirm your messages appear for the unfinished ones.

- [ ] **9. Read the file I/O utilities.**
  Open `include/Utils.h` and `src/Utils.cpp`. Read both files fully. Then search `main.cpp` for any call to `Utils::saveToFile` or `Utils::loadFromFile`. Write a comment at the top of `src/Utils.cpp` answering: are these functions currently called anywhere? What file do they read from/write to? What data do they save?

- [ ] **10. Trace `operator==` on `Student`.**
  Open `include/Student.h` and `src/Student.cpp`. Find the overloaded `operator==`. Write a short comment block above its definition in `Student.cpp` explaining: what two students it considers "equal", and give one example of a case where it would return `true` and one where it would return `false`.

---

## Phase 2: Minor Modifications (Tasks 11–25)

> Goal: Safely change existing behaviour, extend simple logic, and get comfortable editing real code.

- [ ] **11. Add an `age` field to the student display.**
  Open `src/Student.cpp` and find `Student::display()`. It currently prints the student's name and enrolled courses. Modify it to also print the student's age (the `age` member is inherited from `Person` in `include/Person.h`). Build and verify the output changes.

- [ ] **12. Add a `getSalary()` getter to `Professor`.**
  Open `include/Professor.h` and `src/Professor.cpp`. The `salary` member is private but there is no public getter. Add a `getSalary()` method that returns the salary value. Follow the exact style used by `Person::getName()` in `src/Person.cpp`.

- [ ] **13. Add input validation to the "Add Student" flow.**
  Open `main.cpp` and find the `case` that reads a student's name from `std::cin`. Add a check: if the entered name is empty (the user just pressed Enter), print an error message and do not create the student. Do not restructure the surrounding code.

- [ ] **14. Change the `Person` destructor message.**
  Open `src/Person.cpp`. Find the destructor. It currently prints a message when a `Person` is destroyed. Change the message to include the person's name:
  ```
  [Destructor] Person destroyed: <name>
  ```
  Build, run, add a student, then exit to trigger destructor output and verify.

- [ ] **15. Add a `getCourseCount()` method to `Student`.**
  Open `include/Student.h` and `src/Student.cpp`. Add a method `getCourseCount()` that returns the number of courses the student is enrolled in. The enrolled courses are stored in a `std::vector` — use its `.size()` method. Follow the code style of the existing methods.

- [ ] **16. Display the total student count in the "View Students" output.**
  Open `main.cpp` and find the `case` that lists all students. After printing all students, add one line that prints:
  ```
  Total students: <count>
  ```
  Use `Student::count` (the static member from `include/Student.h`) to get the value.

- [ ] **17. Add a `courseName` getter to `Course`.**
  Open `include/Course.h` and `src/Course.cpp`. The `name` member is private. Add a `getName()` getter method that returns the course name as a `const std::string&`. Match the style of `Person::getName()`.

- [ ] **18. Limit student name length.**
  Open `main.cpp` in the "Add Student" case. After reading the student's name, add a check: if the name is longer than 50 characters, print a warning and truncate it to 50 characters using `std::string::substr`. Do not change any class files.

- [ ] **19. Add a `displaySummary()` method to `Professor`.**
  Open `include/Professor.h` and `src/Professor.cpp`. The existing `display()` method prints full details. Add a new `displaySummary()` method that prints only the professor's name and salary on a single line in this format:
  ```
  Prof. <name> | Salary: <salary>
  ```

- [ ] **20. Rename the static counter and update all references.**
  Open `include/Student.h` and `src/Student.cpp`. The static member is named `count`. Rename it to `studentCount` everywhere it appears (declaration in the header, definition in the `.cpp`, and any usage inside Student methods). Build to confirm no compiler errors.

- [ ] **21. Add a `removeCourse()` stub to `Student`.**
  Open `include/Student.h` and `src/Student.cpp`. There is a comment in `Student.cpp` noting a missing "remove course" function. Add a `removeCourse(const std::string& courseName)` method. For now, have it print:
  ```
  [TODO] removeCourse not yet implemented for: <courseName>
  ```
  You'll implement the full logic in a later task.

- [ ] **22. Add a second constructor to `Course`.**
  Open `include/Course.h` and `src/Course.cpp`. The current constructor takes only a course name. Add an overloaded constructor that also accepts an `int` credit hours parameter and stores it in a new private member `creditHours`. The existing constructor should remain unchanged.

- [ ] **23. Add a `getStudentCount()` method to `Course`.**
  Open `include/Course.h` and `src/Course.cpp`. Add a method `getStudentCount()` that returns the number of students currently enrolled in the course (use the size of the students vector). Then update `Course::display()` to print the student count alongside the course name.

- [ ] **24. Modify `Department::display()` to show a course count.**
  Open `src/Department.cpp` and `include/Department.h`. Update `Department::display()` so that before listing the courses, it prints:
  ```
  Department: <name> | Courses: <number>
  ```
  Use the size of the internal courses vector. Do not change any other files.

- [ ] **25. Add age validation to the `Person` constructor.**
  Open `src/Person.cpp` and `include/Person.h`. In the `Person` constructor, add a check: if the supplied `age` is less than 0 or greater than 120, throw a `std::invalid_argument` exception with a descriptive message. Then open `main.cpp` and verify the existing `try-catch` block will catch this exception.

---

## Phase 3: New Micro-Features (Tasks 26–40)

> Goal: Add small, isolated features that follow the existing patterns in the codebase.

- [ ] **26. Implement `removeCourse()` on `Student`.**
  Open `include/Student.h` and `src/Student.cpp`. Complete the `removeCourse()` stub you created in Task 21. Use `std::vector`'s iterator and `erase()` to remove the course whose name matches the argument. If no match is found, print an error message. Look at how `enrollCourse` adds to the vector for reference.

- [ ] **27. Wire up "Add Professor" in the menu.**
  Open `main.cpp`. Find the unimplemented professor `case`. Following the exact same pattern used by the "Add Student" case, implement "Add Professor": prompt for a name, age, and salary; create a `Professor` object; push it into the existing `professors` vector. Look at `include/Professor.h` for the constructor signature.

- [ ] **28. Wire up "View Professors" in the menu.**
  Open `main.cpp`. Implement the "View Professors" case. Follow the exact pattern of the "View Students" case: iterate over the `professors` vector and call `display()` on each. Handle the empty-list case with a message like `"No professors added yet."`.

- [ ] **29. Add a `findStudentByName()` free function.**
  Open `include/Utils.h` and `src/Utils.cpp`. Following the namespace pattern already used for `saveToFile` and `loadFromFile`, add a new function declaration and definition:
  ```cpp
  Student* findStudentByName(const std::vector<Student>& students, const std::string& name);
  ```
  It should return a pointer to the first matching student or `nullptr` if not found. Use the existing `operator==` on `Student` for comparison.

- [ ] **30. Wire up "Add Course" in the menu.**
  Open `main.cpp`. Implement the "Add Course" case. Prompt for a course name, create a `Course` object, and push it into the existing `courses` vector. Follow the "Add Student" pattern. Refer to `include/Course.h` for the constructor signature.

- [ ] **31. Wire up "View Courses" in the menu.**
  Open `main.cpp`. Implement the "View Courses" case following the "View Students" pattern. Iterate over the `courses` vector and call `display()` on each. Print `"No courses added yet."` if the vector is empty.

- [ ] **32. Add an "Enroll Student in Course" menu option.**
  Open `main.cpp`. Add a new menu option (e.g., option `6`): prompt the user for a student name and a course name, search the `students` and `courses` vectors for matches, and if both are found, call `course.addStudent(&student)` and `student.enrollCourse(courseName)`. Print an error if either is not found.

- [ ] **33. Add a `Department` to `main.cpp` and wire its display.**
  Open `main.cpp`. Create one `Department` object. Add a menu option that adds the first course from the `courses` vector into the department (using `Department::addCourse`), and another option that calls `department.display()`. Refer to `include/Department.h` for the method signatures.

- [ ] **34. Add a `setName()` setter to `Person`.**
  Open `include/Person.h` and `src/Person.cpp`. Add a `setName(const std::string& newName)` method. Include the same empty-string guard you added in Task 13: if `newName` is empty, print a warning and leave the name unchanged.

- [ ] **35. Add an "Edit Student Name" menu option.**
  Open `main.cpp`. Add a menu option that prompts for an existing student's name and a new name, finds the student using the `findStudentByName()` utility from Task 29, and calls `setName()` from Task 34. Print a confirmation or a "not found" error.

- [ ] **36. Add a `toString()` method to `Student`.**
  Open `include/Student.h` and `src/Student.cpp`. Add a `toString()` method that returns a `std::string` containing the student's name, age, and comma-separated list of enrolled courses — without printing anything to `std::cout`. This is the data format that `Utils::saveToFile` should eventually use.

- [ ] **37. Implement `saveToFile()` to persist students.**
  Open `src/Utils.cpp` and `include/Utils.h`. Update `saveToFile()` to accept a `const std::vector<Student>&` parameter. Use the `toString()` method from Task 36 to write each student on its own line to `data.txt`. Then call `Utils::saveToFile(students)` from `main.cpp` when the user chooses to exit (case `5`).

- [ ] **38. Add a `Professor` count tracker.**
  Open `include/Professor.h` and `src/Professor.cpp`. Mirror the `Student::studentCount` static member pattern: add a `static int professorCount` to `Professor`, increment it in the constructor, and add a static getter `getProfessorCount()`. Update the "View Professors" output to display the total count at the end.

- [ ] **39. Add a `hasCourse()` method to `Student`.**
  Open `include/Student.h` and `src/Student.cpp`. Add a method `hasCourse(const std::string& courseName)` that returns `true` if the student is already enrolled in the named course, `false` otherwise. Then update `enrollCourse()` to call `hasCourse()` first and print a warning instead of enrolling a duplicate.

- [ ] **40. Add a `findCourseByName()` utility function.**
  Open `include/Utils.h` and `src/Utils.cpp`. Following the same pattern as Task 29's `findStudentByName()`, add:
  ```cpp
  Course* findCourseByName(std::vector<Course>& courses, const std::string& name);
  ```
  Then refactor the "Enroll Student in Course" menu option from Task 32 to use this new utility instead of the inline search loop.

---

## Phase 4: Debugging, Refactoring & Testing (Tasks 41–50)

> Goal: Harden the code, identify edge cases, extract helpers, and write tests for existing logic.

- [ ] **41. Find and fix the raw pointer lifetime bug in `Course`.**
  Open `include/Course.h` and `src/Course.cpp`. The `students` vector stores raw `Student*` pointers. What happens if a `Student` object is destroyed while it is still in a `Course`'s list? Write a comment block in `Course.h` documenting this hazard. Then change the vector type to store `std::string` (student names) instead of pointers — update `addStudent()` and `display()` accordingly.

- [ ] **42. Extract the menu-printing logic into a helper function.**
  Open `main.cpp`. The block of `std::cout` lines that prints the menu is inline in the `while` loop. Extract it into a standalone `void printMenu()` free function defined above `main`. The loop should then call `printMenu()` instead of printing directly. Do not change the menu's content.

- [ ] **43. Extract the "Add Student" case into a helper function.**
  Open `main.cpp`. The code inside the "Add Student" `case` is several lines long. Extract it into a free function `void addStudent(std::vector<Student>& students)`. Replace the original `case` body with a single call to this function. Follow the same pattern for extracting "Add Professor" in Task 44.

- [ ] **44. Extract the "Add Professor" case into a helper function.**
  Open `main.cpp`. Following the exact same pattern as Task 43, extract the "Add Professor" case body into `void addProfessor(std::vector<Professor>& professors)` and replace the case body with a single call.

- [ ] **45. Write a manual test for `Student::enrollCourse` and `hasCourse`.**
  Open `main.cpp` (or create a new file `tests/test_student.cpp` if you prefer). Write a standalone function `void testStudentEnrollment()` that: creates a `Student`, enrolls a course, asserts `hasCourse()` returns `true`, tries to enroll the same course again and verifies the duplicate warning fires, then verifies `getCourseCount()` is still `1`. Call this function at the start of `main` and print PASS/FAIL for each assertion.

- [ ] **46. Write a manual test for `Utils::findStudentByName`.**
  In the same test area as Task 45, write `void testFindStudentByName()`. Create a vector of three `Student` objects with different names. Assert that searching for the second student's name returns a non-null pointer with the correct name. Assert that searching for `"NonExistent"` returns `nullptr`. Print PASS/FAIL.

- [ ] **47. Add edge-case handling to `loadFromFile()`.**
  Open `src/Utils.cpp`. Find `loadFromFile()`. What happens if `data.txt` does not exist? Add a check: if the file cannot be opened, print a clear warning message (e.g., `"[Warning] data.txt not found. Starting with empty data."`) and return without crashing. Test this by deleting `data.txt` and running the program.

- [ ] **48. Refactor repeated vector-printing logic into a template.**
  Open `main.cpp`. The "View Students" and "View Professors" cases both iterate a vector and call `display()` on each element. Extract this into a single template function:
  ```cpp
  template<typename T>
  void displayAll(const std::vector<T>& items, const std::string& label);
  ```
  Replace both case bodies with calls to `displayAll`. Verify it still compiles and behaves identically.

- [ ] **49. Audit and fix all missing `const` correctness.**
  Open `include/Student.h`, `include/Professor.h`, `include/Course.h`, and `include/Department.h`. For every getter method that does not modify the object (e.g., `getName()`, `getSalary()`, `getCourseCount()`), add the `const` qualifier to the end of the method signature if it is missing. Update both the header declarations and the `.cpp` definitions to match. Build and confirm no errors.

- [ ] **50. Write a `validateAge()` free function and centralize age validation.**
  Open `include/Utils.h` and `src/Utils.cpp`. Add a utility function:
  ```cpp
  bool validateAge(int age);
  ```
  that returns `true` if age is between 0 and 120 inclusive. Then open `src/Person.cpp` and replace the inline age-validation logic you added in Task 25 with a call to `Utils::validateAge()`. Write a manual test in the test area from Task 45 that asserts `validateAge(-1)` is false, `validateAge(25)` is true, and `validateAge(121)` is false.

---

## Quick Reference: File Map

| File | Phase most relevant |
|---|---|
| `CMakeLists.txt` | Phase 1 |
| `main.cpp` | All phases |
| `include/Person.h` + `src/Person.cpp` | Phase 1–2 |
| `include/Student.h` + `src/Student.cpp` | Phase 1–4 |
| `include/Professor.h` + `src/Professor.cpp` | Phase 2–3 |
| `include/Course.h` + `src/Course.cpp` | Phase 2–4 |
| `include/Department.h` + `src/Department.cpp` | Phase 1–3 |
| `include/Utils.h` + `src/Utils.cpp` | Phase 3–4 |

---

*Work through tasks in order. Each one builds on the last. Resist the urge to look up solutions — the struggle is the learning.*
