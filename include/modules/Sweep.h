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
     * @param name Name of the module
     * @param startFreq Start frequency of the sweep
     * @param endFreq End frequency of the sweep
     * @param duration Duration of the sweep in seconds
     */
    Sweep(std::string name = "Sweep", double startFreq = 500, double endFreq = 10000, float duration = 10);

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

    /**
     * @brief Update the frequency of the sweep
     * @param frequency New frequency value
     */
    void updateFrequency(float frequency);

    /**
     * @brief Serialize the module settings to an output stream
     * @param ostream Output stream to write the settings to
     */
    void serialize_settings(std::ostream &ostream) override;

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
