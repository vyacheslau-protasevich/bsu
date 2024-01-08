cmake_minimum_required(VERSION 3.26)
project(lab_5_os)

set(CMAKE_CXX_STANDARD 17)

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

add_executable(Server main.cpp)
add_executable(Consume Consume.cpp)
add_executable(runTests tests/consumer_tests.cpp)
target_compile_definitions(runTests PRIVATE TESTING)
target_link_libraries(runTests gtest gtest_main)

