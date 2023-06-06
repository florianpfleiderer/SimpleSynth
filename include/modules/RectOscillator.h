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

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
     void draw() override;

private:
    int _id_output;
    stk::BlitSquare rectangle;

};

#endif //SIMPLESYNTH_RECTOSCILLATOR_H
