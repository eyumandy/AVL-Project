cmake_minimum_required(VERSION 3.22)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

# Compile flags to match the Gradescope test environment
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# Linker flag to specify console subsystem (required for Windows)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,console")

## Fetch Catch2 automatically through CMake
Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2  # Use appropriate Catch2 version
)
FetchContent_MakeAvailable(Catch2)

include_directories(src)

# Main executable for manual testing
add_executable(Main
    src/avl_tree.cpp  # Include AVL tree implementation
    src/main.cpp      # Main function file
)

# Test executable with Catch2 for unit testing
add_executable(Tests
    test/test.cpp     # Your test file
    src/avl_tree.cpp  # Include the AVL tree source in the test target
)

# Link Catch2 to the test executable
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)

# Discover Catch2 tests
include(CTest)
include(Catch)
catch_discover_tests(Tests)
