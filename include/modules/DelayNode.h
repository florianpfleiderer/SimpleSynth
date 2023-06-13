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
 * @details This module delays the input signal by a given amount of samples
 * 
 * @param _id_input
 * @param _id_output
 * @param _id_delay_length
 * @param _delay_length
 * @param _delay
 */
class DelayNode : public Module {
    const int _id_input;
    const int _id_output;
    const int _id_delay_length;
    float _delay_length;

    /*
    * @brief Delay object from stk library
    * @see https://ccrma.stanford.edu/software/stk/classstk_1_1Delay.html
    */
    stk::Delay _delay;

public:
    /**
     * @brief Constructor for initialising default values
     */
    explicit DelayNode();

    /**
     * @brief Construct a new Delay Node object with full controll
     * 
     * @param module_id
     * @param id_input 
     * @param id_output 
     * @param _id_delay_length 
     * @param _delay_length 
     */
    explicit DelayNode(int module_id, int id_input, int id_output, int _id_delay_length, float _delay_length);

    void draw() override;
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    /**
     * @brief Sets the delay length
     * @param delay_length
     * @return true if successful
     */
    bool setDelayLength(float delay_length);

    /**
     * @brief Returns the delay length
     * @return delay_length
     */
    [[nodiscard]] float getDelayLength() const;

    void serialize_settings(std::ostream &ostream) override;

    /**
     * @brief creates a DelayNode object from the given module string of the save-file
     * 
     * @param module_str DelayNode module string from the save-file
     * @param module_id id of the DelayNode object
     * @return std::shared_ptr<Module> to unserialized DelayNode object
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);
};

#endif // SIMPLESYNTH_DELAY_H