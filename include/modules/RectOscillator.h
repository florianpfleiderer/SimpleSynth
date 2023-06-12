//
// Created by Cheetah on 02.06.2023.
//

#ifndef SIMPLESYNTH_RECTOSCILLATOR_H
#define SIMPLESYNTH_RECTOSCILLATOR_H

#include "Oscillator.h"
#include "BlitSquare.h"

class RectOscillator : public Oscillator {
public:
    RectOscillator();
    RectOscillator(int id, int id_output, float frequency);

    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
    void draw() override;

private:
    stk::BlitSquare rectangle;

    void updateFrequency(float freqency) override;
};

#endif //SIMPLESYNTH_RECTOSCILLATOR_H
