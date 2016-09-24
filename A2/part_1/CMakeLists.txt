cmake_minimum_required(VERSION 2.8)

project(bicycle)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(
    include
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(GLUT_HDRS
    include/glut/point.hpp
    include/glut/vector.hpp
    include/glut/performance_timer.hpp
    include/glut/keyboard.hpp
    include/glut/glut_framework.hpp)
set(GLUT_SRCS
    src/glut/glut_framework.cpp
    src/glut/keyboard.cpp
    src/glut/performance_timer.cpp
)

add_library(glut_framework ${GLUT_SRCS} ${GLUT_HDRS})
target_link_libraries(glut_framework ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

add_executable(glut_test src/glut/main.cpp)
add_dependencies(glut_test glut_framework)
target_link_libraries(glut_test
    ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glut_framework)
