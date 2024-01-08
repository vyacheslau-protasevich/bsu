cmake_minimum_required(VERSION 3.27)
project(lab_1_os)

set(CMAKE_CXX_STANDARD 17)

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

add_executable(lab_1_os task.cpp)
add_executable(lab_1_os_98 task_98.cpp)

add_executable(main_tests main_tests.cpp)
target_compile_definitions(main_tests PRIVATE TESTING)
target_link_libraries(main_tests gtest_main)
add_test(NAME main_tests COMMAND main_tests)

# Link the test executable with Google Test
target_link_libraries(main_tests gtest gtest_main)


