cmake_minimum_required(VERSION 3.26)
project(os_lab_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(os_lab_2 main.cpp)
add_executable(parent parent.cpp)
add_executable(child child.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Debug)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/aa2e91fd6918519dafa3bee4aa706d04857e7d06.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(runTests tests/child_tests.cpp
        tests/parent_tests.cpp)
target_compile_definitions(runTests PRIVATE TESTING)
target_compile_definitions(runTests PRIVATE TESTING1)
target_link_libraries(runTests gtest_main)
#add_test(NAME lab_2_os COMMAND runTests)

# Link the test executable with Google Test
target_link_libraries(runTests gtest gtest_main)

