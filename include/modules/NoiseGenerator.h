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
    NoiseGenerator(int id,  int id_output, float frequency);    

    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
    void draw() override;

private:
    stk::Noise noise;

    void updateFrequency(float freqency) override;
};

#endif //SIMPLESYNTH_NOISEGENERATOR_H
