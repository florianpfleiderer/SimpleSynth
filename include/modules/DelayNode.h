//
// Created by Florian Pfleiderer on 04.06.2023.
//

#ifndef SIMPLESYNTH_DELAY_H
#define SIMPLESYNTH_DELAY_H

#include "Module.h"
#include "Stk.h"
#include "Delay.h"

/**
 * @brief Delay Module
 */
class DelayNode : public Module {
    const int _id_input;
    const int _id_output;
    const int _id_delay_length;
    float _delay_length;
    stk::Delay _delay;
    bool setDelayLength(float delay_length);

public:
    /**
     * @brief Constructor
     */
    explicit DelayNode();

    void draw() override;
    bool tick(stk::StkFloat *buffer, unsigned int nBufferFrames, double streamTime, int output_id) override;
};

#endif // SIMPLESYNTH_DELAY_H