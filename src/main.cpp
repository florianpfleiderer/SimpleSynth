#include <iostream>

#include "imnodes.h"

#include "../include/ModuleEditor.h"


int main() {

    stk::Stk::setSampleRate(44100.0);
<<<<<<< HEAD
    ModuleEditor editor(WindowHost::create_window(1280, 720, "SimpleSynth"));
=======
    
    ModuleEditor editor;
>>>>>>> main

    while (!glfwWindowShouldClose(editor.getWindow())) {
        glfwPollEvents();

        editor.show();
    }

    return 0;
}
