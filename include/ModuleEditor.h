//
// Created by Robert Ristic on 19.05.23.
//

#ifndef SIMPLESYNTH_MODULEEDITOR_H
#define SIMPLESYNTH_MODULEEDITOR_H

#include "GLFW/glfw3.h"

#include "IdGenerator.h"

#include "modules/Module.h"

class ModuleEditor {
public:
    ModuleEditor();
    virtual ~ModuleEditor();
    [[nodiscard]] GLFWwindow* getWindow() const;
    void show();

private:
    GLFWwindow* const window;
    const IdGenerator _idGenerator;
    std::vector<std::shared_ptr<Module>> _modules;
    std::vector<Connection> _connections;

    [[nodiscard]] std::shared_ptr<Module> getModuleByConnectorId(int id) const;

    static void glfw_error_callback(int error, const char* description);
    static GLFWwindow* create_window(int width, int height, const char* title);
    static void begin_frame();
    static void end_frame(GLFWwindow* window, ImVec4 background_color);
    static void shutdown(GLFWwindow* window);
};


#endif //SIMPLESYNTH_MODULEEDITOR_H
