# src/CMakeLists.txt

# Gather all source files
set(SRC_FILES
        Specs.cpp
        datastructures/dynamicArray.cpp
        Entities/EntityManager.cpp
)

# Create a static library
add_library(Specs STATIC ${SRC_FILES})

target_include_directories(Specs
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
