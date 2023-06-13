#include <iostream>

#include "imnodes.h"

#include "../include/ModuleEditor.h"


int main() {

    ModuleEditor editor;

    while (!glfwWindowShouldClose(editor.getWindow())) {
        glfwPollEvents();

        editor.show();
    }

    return 0;
}
