//
// Created by Moritz Mairhofer on 30.05.23.
//

#ifndef SIMPLESYNTH_AMPLIFIER_H
#define SIMPLESYNTH_AMPLIFIER_H

#include "Module.h"

class Amplifier : public Module {
    int _id_output;
    int _id_input;
public:
    Amplifier();
    void draw() override;
};

#endif
