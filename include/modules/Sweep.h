//
// Created by Cheetah on 09.06.2023.
//

#ifndef SIMPLESYNTH_SWEEP_H
#define SIMPLESYNTH_SWEEP_H

#include "Stk.h"
#include "imnodes.h"
#include "SineWave.h"
#include "../../include/IdGenerator.h"
#include "Module.h"

/**
 * @brief Sweep class represents a module that generates a frequency sweep
 */
class Sweep : public Module {
public:
    /**
     * @brief Constructor for the Sweep class
     * @param startFreq Start frequency of the sweep
     * @param endFreq End frequency of the sweep
     * @param duration Duration of the sweep in seconds
     */
    Sweep(float startFreq = 500, float endFreq = 10000, float duration = 10);

    /**
     * @brief Construct a new Sweep object with full controll
     * 
     * @param startFreq 
     * @param endFreq 
     * @param duration 
     * @param module_id 
     * @param id_output 
     * @param id_start_frequency 
     * @param id_end_frequency 
     * @param id_duration 
     */
    Sweep(float startFreq, float endFreq, float duration, int module_id, int id_output, int id_start_frequency, int id_end_frequency, int id_duration );

    /**
     * @brief Draw the module node in the user interface
     */
    void draw() override;

    /**
     * @brief Processe audio frames and generates the frequency sweep
     * @param frames Audio frames to process
     * @param streamTime Stream time in seconds
     * @param output_id ID of the output connector
     * @return True if the processing is successful, false otherwise
     */
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    void startSweep();
    void stopSweep();

    void serialize_settings(std::ostream &ostream) override;

    /**
     * @brief creates a Sweep object from the given module string of the save-file
     * 
     * @param module_str Sweep module string from the save-file
     * @param module_id id of the Sweep object
     * @return std::shared_ptr<Module> to unserialized Sweep object
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);

private:
    stk::SineWave sineWave;        /**< Sine wave generator used for the sweep. */
    float sweepStartFrequency;     /**< Start frequency of the sweep. */
    float sweepEndFrequency;       /**< End frequency of the sweep. */
    float sweepDuration;           /**< Duration of the sweep in seconds. */
    double startTime;              /**< Start time of the sweep in milliseconds. */
    bool isSweeping;               /**< Flag indicating if the sweep is currently active. */
    int _id_output;                /**< ID of the output connector. */
    int _id_start_frequency;       /**< ID of the start frequency attribute. */
    int _id_end_frequency;         /**< ID of the end frequency attribute. */
    int _id_duration;              /**< ID of the duration attribute. */
};

#endif //SIMPLESYNTH_SWEEP_H
