cmake_minimum_required(VERSION 3.24)
include(FetchContent)

project(SimpleSynthTests VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

#gtest
FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG 001f281926c74a819e9266bb4ec525515ff39418
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  hello_test
  hello_test.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)