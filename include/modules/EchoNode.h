//
// Created by Florian Pfleiderer on 05.06.2023.
//

#ifndef SIMPLESYNTH_ECHO_H
#define SIMPLESYNTH_ECHO_H

#include "Module.h"
#include "Stk.h"
#include "Echo.h"

/**
 * @brief ECHO Module
 */
class EchoNode : public Module {
    const int _id_input;
    const int _id_output;
    const int _id_echo_delay;
    float _echo_delay;

    stk::Echo _echo;
    bool setEchoDelay(float echo_delay);

public:
    /**
     * @brief Constructor
     */
    explicit EchoNode();

    void draw() override;
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
};

#endif // SIMPLESYNTH_ECHO_H