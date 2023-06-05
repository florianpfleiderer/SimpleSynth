#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "Module.h"

class Oscillator : public Module {
public:

    Oscillator(std::string name);

    void draw() override;

    ~Oscillator() override;

    bool tick(stk::StkFloat *buffer, unsigned int nBufferFrames, double streamTime, int output_id) override;

    int _id_output;
};

#endif // OSCILLATOR_H