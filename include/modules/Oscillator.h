#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "Module.h"

class Oscillator : public Module {
public:
    Oscillator();

    void draw();

    bool tick(double *buffer, unsigned int nBufferFrames, double streamTime, int output_id);
};

#endif // OSCILLATOR_H