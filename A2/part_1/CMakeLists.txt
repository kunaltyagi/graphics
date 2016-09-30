cmake_minimum_required(VERSION 3.1)

project(bicycle)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Threads REQUIRED)

include_directories(
    include
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wextra -O0 -pedantic"
)
set(CMAKE_BUILD_TYPE Debug)

set(GLUT_HDRS
    include/glut/point.hpp
    include/glut/vector.hpp
    include/glut/performance_timer.hpp
    include/glut/keyboard.hpp
    include/glut/glut_framework.hpp
)
set(GLUT_SRCS
    src/glut/glut_framework.cpp
    src/glut/keyboard.cpp
    src/glut/performance_timer.cpp
)
set(HDRS
    include/joint.hpp
    include/object.hpp
    include/generic_object.hpp
    include/viewport.hpp
    include/cylinder.hpp
    include/cube.hpp
    include/sphere.hpp
    include/torus.hpp
    #    include/torus_old.hpp
    include/objects.hpp
    include/triangle.hpp
)
set(SRCS
    src/viewport.cpp
    src/generic_object.cpp
    src/cube.cpp
)

set(LIBS
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    Threads::Threads
)

add_library(glut_framework ${GLUT_SRCS} ${GLUT_HDRS})
target_link_libraries(glut_framework ${LIBS})

add_executable(bicycle src/main.cpp ${HDRS} ${SRCS})
add_dependencies(bicycle glut_framework)
target_link_libraries(bicycle glut_framework ${LIBS})

add_executable(glut_test src/glut/main.cpp)
add_dependencies(glut_test glut_framework)
target_link_libraries(glut_test glut_framework ${LIBS})
