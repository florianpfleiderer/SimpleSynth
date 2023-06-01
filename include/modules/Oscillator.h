//
// Created by Robert Ristic on 16.05.23.
//

#ifndef SIMPLESYNTH_OSCILLATOR_H
#define SIMPLESYNTH_OSCILLATOR_H

#include "Module.h"
class Oscillator : public Module {
    int _id_output;
public:
    bool tick(stk::StkFloat *buffer, unsigned int nBufferFrames, double streamTime, int output_id) override;

    Oscillator();
    void draw() override;
};

#endif // SIMPLESYNTH_OSCILLATOR_H
