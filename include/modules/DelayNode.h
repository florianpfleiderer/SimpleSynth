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
    const int _id_delay_time;
    const int _id_feedback;
    float _delay_time;
    float _feedback;
    stk::Delay _delay;

public:
    /**
     * @brief Constructor
     */
    explicit DelayNode();

    void draw() override;
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
};

#endif // SIMPLESYNTH_DELAY_H