//
// Created by Cheetah on 09.06.2023.
//

#ifndef SIMPLESYNTH_SWEEP_H
#define SIMPLESYNTH_SWEEP_H

#include "Stk.h"
#include "imnodes.h"
#include "SineWave.h"
#include "../../include/IdGenerator.h"
#include "Module.h"

class Sweep : public Module {
public:
    Sweep(std::string name = "Sweep", double startFreq = 500, double endFreq = 10000, float duration = 10);

    void startSweep();
    void stopSweep();
    void draw();
    bool tick(stk::StkFrames &frames, double streamTime, int output_id);
    void updateFrequency(float frequency);
    void serialize_settings(std::ostream &ostream) override;

private:
    stk::SineWave sineWave;
    float sweepStartFrequency;
    float sweepEndFrequency;
    float sweepDuration;
    double startTime;
    bool isSweeping;
    int _id_output;
    int _id_start_frequency;
    int _id_end_frequency;
    int _id_duration;
};

#endif //SIMPLESYNTH_SWEEP_H
