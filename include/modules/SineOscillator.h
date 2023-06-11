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
    SineOscillator(int id, int id_output, float frequency);

    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);
    
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
    void draw() override;

private:
    stk::SineWave sine;

    void updateFrequency(float freqency) override;
};

#endif // SINE_OSCILLATOR_H