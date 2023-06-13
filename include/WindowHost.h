//
// Created by Florian Pfleiderer on 13.06.2023.
//

#ifndef SIMPLESYNTH_WINDOWHOST_H
#define SIMPLESYNTH_WINDOWHOST_H

#include <fstream>
#include <regex>
#include <memory>

#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>

class WindowHost {
public:
    static void glfw_error_callback(int error, const char* description);
    static GLFWwindow* create_window(int width, int height, const char* title);
    // static void end_frame(GLFWwindow* window, ImVec4 background_color);
    static void shutdown(GLFWwindow* window);
};

#endif //SIMPLESYNTH_WINDOWHOST_H