//
// Created by Dennis Waniek on 31.05.2023.
//

#ifndef SIMPLESYNTH_SEQUENCER_H
#define SIMPLESYNTH_SEQUENCER_H

#include "Module.h"
#include <algorithm>

#define INPUT_SIZE 4

class Sequencer : public Module {
    const int _id_output;
    std::vector<unsigned int> _ids_input;
    int bpm;

public:
    Sequencer(int input_size=4, int beats_per_minute=60);

    ~Sequencer() override;

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    void draw() override;



};

#endif //SIMPLESYNTH_SEQUENCER_H