cmake_minimum_required(VERSION 3.20.0)

project (test_task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# List lib
add_library(List STATIC src/List.cpp)
target_include_directories(List PUBLIC src)

# FleIO lib
add_library(FileIO INTERFACE)
target_include_directories(FileIO INTERFACE src)
target_link_libraries(FileIO INTERFACE List)

# main target
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE FileIO)

# testing
enable_testing()
add_subdirectory(tests)

add_custom_target(run
    COMMAND main
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
