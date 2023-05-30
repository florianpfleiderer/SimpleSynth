//
// Created by Moritz Mairhofer on 30.05.23.
//

#ifndef SIMPLESYNTH_MIXER_H
#define SIMPLESYNTH_MIXER_H

#include "Module.h"

class Mixer : public Module {
    int _id_output;
    int _id_input;
public:
    Mixer();
    void draw() override;
};

#endif