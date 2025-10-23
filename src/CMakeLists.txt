# src/CMakeLists.txt

# Gather all source files
set(SRC_FILES
        Aspecs.cpp
        datastructures/dynamicArray.cpp
        Entities/EntityManager.cpp
        datastructures/resourcePool.cpp
)

# Create a static library
add_library(AspECS STATIC ${SRC_FILES})

target_include_directories(AspECS
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
