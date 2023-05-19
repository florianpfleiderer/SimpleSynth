cmake_minimum_required(VERSION 3.24)
project(SimpleSynth)

#include(ExternalProject)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_TESTS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_INSTALL OFF CACHE BOOL  "GLFW lib only" )

# glad
FetchContent_Declare(glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG df8e9e16110b305479a875399cee13daa0ccadd9
        )
# glfw
FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.2
        )
# imgui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.89.3 #v1.89.4 breaks current imnodes version!
)
FetchContent_Declare(
        imnodes
        GIT_REPOSITORY https://github.com/Nelarius/imnodes.git
        GIT_TAG v0.5
)


FetchContent_MakeAvailable(glad)
FetchContent_MakeAvailable(glfw)

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
    message("${IMNODES_HEADERS}")
    add_library(imnodes STATIC ${IMNODES_SOURCES} ${IMNODES_HEADERS})
    target_link_libraries(imnodes PUBLIC imgui)
endif ()

add_executable(SimpleSynth main.cpp)
target_link_libraries(SimpleSynth glad glfw imgui imnodes)
include_directories(${imnodes_SOURCE_DIR})
