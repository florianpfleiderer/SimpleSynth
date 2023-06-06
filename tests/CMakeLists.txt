cmake_minimum_required(VERSION 3.24)
include(FetchContent)

project(SimpleSynthTests VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

#gtest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG 001f281926c74a819e9266bb4ec525515ff39418
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

set(TEST_NAMES "")
# list(APPEND TEST_NAMES "hello_test")
list(APPEND TEST_NAMES "node_test")
list(APPEND TEST_NAMES "oscillator_test")

# Make an executable from every test
foreach(TEST ${TEST_NAMES})
      add_executable(${TEST} 
        ${TEST}.cpp
        ../src/ModuleEditor.cpp
        ../include/ModuleEditor.h
        ../src/modules/DelayNode.cpp
        ../src/modules/EchoNode.cpp
        ../src/modules/Module.cpp
        ../src/modules/Output.cpp
        ../src/modules/Oscillator.cpp
        ../include/IdGenerator.h
        ../src/modules/RectOscillator.cpp
        ../src/modules/SineOscillator.cpp)
      target_include_directories(${TEST} PRIVATE ../include/modules)
      target_link_libraries(${TEST} 
        GTest::gtest_main
        glad
        glfw
        imgui
        imnodes
        stk)

      # add to gtest
      gtest_discover_tests(${TEST})
endforeach(TEST ${TEST_NAMES})
