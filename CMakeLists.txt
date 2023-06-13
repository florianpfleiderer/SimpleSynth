cmake_minimum_required(VERSION 3.24)
include(FetchContent)

project(SimpleSynth VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_TESTS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_definitions(-D_USE_MATH_DEFINES) # needed for stk on windows

# glad
FetchContent_Declare(glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG df8e9e16110b305479a875399cee13daa0ccadd9
        )
# glfw
FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
        )
# imgui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.89.3 #v1.89.4 breaks current imnodes version!
)
#imnodes
FetchContent_Declare(
        imnodes
        GIT_REPOSITORY https://github.com/Nelarius/imnodes.git
        GIT_TAG v0.5
)
#stk
FetchContent_Declare(
        stk
        GIT_REPOSITORY https://github.com/thestk/stk.git
        GIT_TAG cc2dd22e9752bf5fd94f0799e01d19d5e8399058
)

# only for licence
FETCHCONTENT_DECLARE(
        imguitemplate
        GIT_REPOSITORY https://github.com/JulesFouchy/Simple-ImGui-Setup.git
        GIT_TAG origin/main
)
FetchContent_Populate(imguitemplate)

FetchContent_MakeAvailable(glad)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(stk)

FetchContent_GetProperties(imgui)
if (NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
    set(IMGUI_INCLUDE_DIR ${imgui_SOURCE_DIR}/)
    file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp)
    file(GLOB IMGUI_HEADERS ${imgui_SOURCE_DIR}/*.h)
    add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS} ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)
    add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
    target_include_directories(imgui PUBLIC ${IMGUI_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDE_DIR})
    target_link_libraries(imgui ${OPENGL_LIBRARIES} glfw glad)
endif ()

FetchContent_getProperties(imnodes)
if (NOT imnodes_POPULATED)
    FetchContent_Populate(imnodes)
    file(GLOB IMNODES_SOURCES ${imnodes_SOURCE_DIR}/*.cpp)
    file(GLOB IMNODES_HEADERS ${imnodes_SOURCE_DIR}/*.h)
    add_library(imnodes STATIC ${IMNODES_SOURCES} ${IMNODES_HEADERS})
    target_link_libraries(imnodes PUBLIC imgui)
endif ()

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/ModuleEditor.cpp
        include/ModuleEditor.h
        src/WindowHost.cpp
        include/WindowHost.h
        src/modules/DelayNode.cpp
        src/modules/EchoNode.cpp
        src/modules/Module.cpp
        src/modules/Output.cpp
        src/modules/Oscillator.cpp
        include/IdGenerator.h
        include/modules/Sequencer.h
        src/modules/Sequencer.cpp
        src/modules/SineOscillator.cpp
        src/modules/RectOscillator.cpp
        include/modules/SawOscillator.h
        src/modules/SawOscillator.cpp
        include/modules/NoiseGenerator.h
        src/modules/NoiseGenerator.cpp 
        src/modules/Sweep.cpp 
        include/modules/Sweep.h)

target_link_libraries(${PROJECT_NAME} glad glfw imgui imnodes stk)
include_directories(${imnodes_SOURCE_DIR})
include_directories(${stk_SOURCE_DIR}/include)

# Enable many good warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /WX /W3)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -Wpedantic -pedantic-errors)
endif()

################## DOCUMENTATION ################
set(PROJECT_ROOT_NAME ${PROJECT_NAME})
set(PROJECT_ROOT_VERSION ${PROJECT_VERSION})
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_ROOT_BINARY_DIR ${CMAKE_BINARY_DIR})

option(BUILD_DOCS "Build documentation" ON)
if(BUILD_DOCS)
    add_subdirectory(docs)
    add_dependencies(${PROJECT_NAME} doc_doxygen)
endif()

################## TESTING ################
#option(BUILD_TESTS "Build tests" ON)
#if(BUILD_TESTS)
#        enable_testing()
#        add_subdirectory(tests)
#endif()