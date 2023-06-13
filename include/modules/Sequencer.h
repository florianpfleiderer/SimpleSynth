//
// Created by Dennis Waniek on 31.05.2023.
//

#ifndef SIMPLESYNTH_SEQUENCER_H
#define SIMPLESYNTH_SEQUENCER_H

#include "Module.h"
#include <algorithm>
#include "Stk.h"

#define INPUT_SIZE 4

class Sequencer : public Module {
private:
    const int _id_bpm;
    const int _id_output;
    std::vector<int> _ids_input;
    int _bpm = 60;
    //[[maybe_unused]] int _selected_bpm = 1;

public:
    Sequencer(unsigned int input_size = 4);

    ~Sequencer() override;

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    void draw() override;

    void serialize_settings(std::ostream &ostream) override;

};

#endif //SIMPLESYNTH_SEQUENCER_H