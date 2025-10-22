# src/CMakeLists.txt

# Gather all source files
set(SRC_FILES
        Specs.cpp
        datastructures/dynamicArray.cpp
        Entities/EntityManager.cpp
)

# Create a static library
add_library(Aspecs STATIC ${SRC_FILES})

target_include_directories(Aspecs
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
