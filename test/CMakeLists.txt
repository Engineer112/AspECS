#test/CmakeList.txt

# -------------------------------
# Fetch GoogleTest
# -------------------------------
include(FetchContent)

# Configure gtest safely for MSVC before making available
if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)   # Use shared CRT
    set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)   # Disable pthreads
    set(gtest_build_tests OFF CACHE BOOL "" FORCE)       # Do not build gtest's internal tests
endif()

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of googletest" FORCE)
FetchContent_MakeAvailable(googletest)

# -------------------------------
# Find all test cpp files
# -------------------------------
file(GLOB TEST_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# If no test files exist, create a dummy one
if(TEST_FILES STREQUAL "")
    message(STATUS "No test files found. Creating dummy test.")
    set(DUMMY_TEST "${CMAKE_CURRENT_BINARY_DIR}/dummy_test.cpp")
    file(WRITE ${DUMMY_TEST} "
#include <gtest/gtest.h>

TEST(DummyTest, AlwaysPasses) {
    EXPECT_TRUE(true);
}
")
    list(APPEND TEST_FILES ${DUMMY_TEST})
endif()

# -------------------------------
# Create test executable
# -------------------------------
add_executable(unit_tests ${TEST_FILES}
        dynamicArrayTests.cpp
        resourcePoolTests.cpp
        #tests:
)

# Link gtest and your engine library
target_link_libraries(unit_tests PRIVATE gtest_main Aspecs)

# -------------------------------
# Register tests with CTest
# -------------------------------
include(GoogleTest)
gtest_discover_tests(unit_tests)
