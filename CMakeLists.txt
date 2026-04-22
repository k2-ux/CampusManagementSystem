cmake_minimum_required(VERSION 3.10)
project(CampusManagementSystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(CampusManagementSystem
    main.cpp
    src/Person.cpp
    src/Student.cpp
    src/Professor.cpp
    src/Course.cpp
    src/Department.cpp
    src/Utils.cpp
)