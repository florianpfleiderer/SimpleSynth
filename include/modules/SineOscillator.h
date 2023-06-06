//
// Created by Theresa Freibauer on 31.05.2023.
//
#ifndef SINE_OSCILLATOR_H
#define SINE_OSCILLATOR_H

#include "Oscillator.h"
#include "Stk.h"
#include "SineWave.h"

class SineOscillator : public Oscillator {
public:
    SineOscillator();

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    void draw() override;

private:
    int _id_output;
    stk::SineWave sine;
};

#endif // SINE_OSCILLATOR_H