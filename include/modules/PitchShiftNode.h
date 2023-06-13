//
// Created by Florian Pfleiderer on 04.06.2023.
//

#ifndef SIMPLESYNTH_PITCH_H
#define SIMPLESYNTH_PITCH_H

#include "Module.h"
#include "Stk.h"
#include "PitShift.h"

/**
 * @brief PitchShift Module
 * @details This module shifts the pitch of the input signal by a given amount of semitones
 * 
 * @param _id_input
 * @param _id_output
 * @param _id_pitch_shift
 * @param _pitch_shift
 * @param _pitch
 */
class PitchShiftNode : public Module {
    const int _id_input;
    const int _id_output;
    const int _id_pitch_shift;
    float _pitch_shift;

    /*
    * @brief PitchShift object from stk library
    * @see https://ccrma.stanford.edu/software/stk/classstk_1_1PitchShift.html
    */
    stk::PitShift _pitch;

public: 
    /**
     * @brief Constructor for initialising default values
     */
    explicit PitchShiftNode();

    /**
     * @brief Construct a new Pitch Shift Node object with full control
     * 
     * @param module_id
     * @param id_input 
     * @param id_output 
     * @param _id_pitch_shift 
     * @param _pitch_shift 
     */
    explicit PitchShiftNode(int module_id, int id_input, int id_output, int _id_pitch_shift, float _pitch_shift);

    void draw() override;
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    /**
     * @brief Sets the pitch shift
     * @param pitch_shift
     * @return true if successful
     */
    void setPitchShift(float pitch_shift);

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





#endif //SIMPLESYNTH_PITCH_H