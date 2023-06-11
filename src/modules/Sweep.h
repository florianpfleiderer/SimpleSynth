//
// Created by Cheetah on 09.06.2023.
//

#ifndef SIMPLESYNTH_SWEEP_H
#define SIMPLESYNTH_SWEEP_H

#include "../../include/modules/Oscillator.h"
#include "Stk.h"
#include "imnodes.h"
#include "SineWave.h"

class Sweep: public Oscillator {
private:
    stk::SineWave sineWave;
    double sweepStartFrequency;
    double sweepEndFrequency;
    double sweepDuration;
    double startTime;
    bool isSweeping;

public:
    Sweep(double startFreq = 500, double endFreq = 10000, double duration = 10);

    void startSweep();
    void stopSweep();

    void draw() override;
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
};

#endif //SIMPLESYNTH_SWEEP_H
