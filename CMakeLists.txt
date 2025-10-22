cmake_minimum_required(VERSION 4.0)
project(Aspecs)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

option(BUILD_SANDBOX "Build the sandbox app" ON)
if(BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif()

# -----------------------------
# Unit tests
# -----------------------------
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
