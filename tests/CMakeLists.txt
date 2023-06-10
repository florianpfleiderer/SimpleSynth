cmake_minimum_required(VERSION 3.24)

project(SimpleSynthTests VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

# catch2 testing framework
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.2
)

FetchContent_MakeAvailable(Catch2)

include(CTest)
include(Catch)

file(GLOB CPP_FILES "../src/modules/*.cpp")

set(TEST_NAMES "")
list(APPEND TEST_NAMES "id_generator_test")
list(APPEND TEST_NAMES "node_test")
list(APPEND TEST_NAMES "template_test_example")

foreach(TEST_NAME ${TEST_NAMES})
        add_executable(${TEST_NAME}
                ${CPP_FILES}
                ${TEST_NAME}.cpp
        )

        target_link_libraries(${TEST_NAME}
                PRIVATE
                Catch2::Catch2WithMain
                glad
                glfw
                imgui
                imnodes
                stk
        )

        include_directories(${imnodes_SOURCE_DIR})
        include_directories(${stk_SOURCE_DIR}/include)

        catch_discover_tests(${TEST_NAME})
endforeach(TEST_NAME ${TEST_NAMES})

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)