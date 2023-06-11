//
// Created by Cheetah on 08.06.2023.
//

#ifndef SIMPLESYNTH_SAWOSCILLATOR_H
#define SIMPLESYNTH_SAWOSCILLATOR_H

#include "Oscillator.h"
#include "Stk.h"
#include "BlitSaw.h"

class SawOscillator : public Oscillator {
public:
    SawOscillator();
    SawOscillator(int id, int id_output, float frequency);

    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
    void draw() override;

private:
    stk::BlitSaw saw;

    void updateFrequency(float frequency) override;
};

#endif //SIMPLESYNTH_SAWOSCILLATOR_H
