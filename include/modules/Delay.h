//
// Created by Florian Pfleiderer on 04.06.2023.
//

#ifndef SIMPLESYNTH_DELAY_H
#define SIMPLESYNTH_DELAY_H

#include "Module.h"

/**
 * @brief Delay Module
 */
class Delay : public Module {
    const int _id_input;
    const int _id_output;
    float _delay_time;
    float _feedback;
    const std::string _name;
public:
    /**
     * @brief Constructor
     */
    explicit Delay();

    void draw() override;
    bool tick(stk::StkFloat *buffer, unsigned int nBufferFrames, double streamTime, int output_id) override;

};

#endif // SIMPLESYNTH_DELAY_H