//
// Created by wanie on 31.05.2023.
//

#ifndef SIMPLESYNTH_SEQUENCER_H
#define SIMPLESYNTH_SEQUENCER_H

#include "Module.h"

class Sequencer : public Module {
    int _id_output;
    int bpm;

public:
    Sequencer(int beats_per_minute);
    void draw() override;

};

#endif //SIMPLESYNTH_SEQUENCER_H