#include <iostream>

#include "imnodes.h"

#include "../include/ModuleEditor.h"


int main() {

    stk::Stk::setSampleRate(44100.0);


    ModuleEditor editor;

    while (!glfwWindowShouldClose(editor.getWindow())) {
        glfwPollEvents();

        editor.show();
    }

    return 0;
}
