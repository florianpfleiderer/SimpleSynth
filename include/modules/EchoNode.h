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

    /**
     * @brief Construct a new Echo Node object with full control
     * 
     * @param id_input 
     * @param id_output 
     * @param id_echo_delay 
     * @param echo_delay 
     */
    explicit EchoNode(int module_id, int id_input, int id_output, int id_echo_delay, float echo_delay);

    void draw() override;
    bool play(bool state) override;
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
    
    void serialize_settings(std::ostream &ostream) override;

    /**
     * @brief creates a EchoNode object from the given module string of the save-file
     * 
     * @param module_str EchoNode module string from the save-file
     * @param module_id id of the EchoNode object
     * @return std::shared_ptr<Module> to unserialized EchoNode object
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);
};

#endif // SIMPLESYNTH_ECHO_H