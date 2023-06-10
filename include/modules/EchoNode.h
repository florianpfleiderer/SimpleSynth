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
 * @details This module delays the input signal by a given amount of samples
 * 
 * @param _id_input
 * @param _id_output
 * @param _id_echo_delay
 * @param _echo_delay
 * @param _echo
 */
class EchoNode : public Module {
    const int _id_input;
    const int _id_output;
    const int _id_echo_delay;
    float _echo_delay;

    /**
    * @brief Echo object from stk library
    * @see https://ccrma.stanford.edu/software/stk/classstk_1_1Echo.html
    * 
    */
    stk::Echo _echo;

    /**
    * @brief Sets the echo delay
    * @param echo_delay
    * @return true if successful
    */
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