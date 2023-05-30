//
// Created by Moritz Mairhofer on 30.05.23.
//

#ifndef SIMPLESYNTH_OSCILLATOR_H
#define SIMPLESYNTH_OSCILLATOR_H

#include "Module.h"
class Amplifier : public Module {
    int _id_output;
public:
    Amplifier();
    void draw() override;
};


