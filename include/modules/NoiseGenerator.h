//
// Created by Cheetah on 08.06.2023.
//

#ifndef SIMPLESYNTH_NOISEGENERATOR_H
#define SIMPLESYNTH_NOISEGENERATOR_H

#include "Oscillator.h"
#include "Stk.h"
#include <Noise.h>

class NoiseGenerator : public Oscillator {
public:
    NoiseGenerator();

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    void draw() override;

private:
    int _id_output;
    stk::Noise noise;
};

#endif //SIMPLESYNTH_NOISEGENERATOR_H
