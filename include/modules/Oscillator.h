//
// Created by Robert Ristic on 16.05.23.
//

#ifndef SIMPLESYNTH_OSCILLATOR_H
#define SIMPLESYNTH_OSCILLATOR_H

#include "Module.h"
class Oscillator : public Module {
    int _id_output;
public:
    Oscillator();
    void draw() override;
};

#endif // SIMPLESYNTH_OSCILLATOR_H
