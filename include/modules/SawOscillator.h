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

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    void draw() override;

private:
    int _id_output;
    stk::BlitSaw saw;

};

#endif //SIMPLESYNTH_SAWOSCILLATOR_H
