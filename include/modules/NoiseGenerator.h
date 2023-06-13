//
// Created by Cheetah on 08.06.2023.
//

#ifndef SIMPLESYNTH_NOISEGENERATOR_H
#define SIMPLESYNTH_NOISEGENERATOR_H

#include "Module.h"
#include "Stk.h"
#include <Noise.h>

class NoiseGenerator : public Module {
public:
    NoiseGenerator();
    NoiseGenerator(int id,  int id_output);

    //static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
    void draw() override;
    void serialize_settings(std::ostream &ostream) override;

private:
    stk::Noise noise;

    int _id_output;
};

#endif //SIMPLESYNTH_NOISEGENERATOR_H
