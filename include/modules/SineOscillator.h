//
// Created by Theresa Freibauer on 31.05.2023.
//
#ifndef SINE_OSCILLATOR_H
#define SINE_OSCILLATOR_H

#include "Oscillator.h"
#include "Stk.h"
#include "SineWave.h"

/**
 * @brief A module representing a Sine Oscillator
 */
class SineOscillator : public Oscillator {
public:
    /**
     * @brief Default constructor
     * Construct a SineOscillator object with default parameters
     * Default frequency is set to 440.0 Hz
     */
    SineOscillator();

    /**
     * @brief Constructor.
     * Construct a SineOscillator object with the specified parameters
     * @param id ID of the module
     * @param id_output ID of the output connector
     * @param frequency Frequency of the oscillator
     */
    SineOscillator(int id, int id_output, float frequency);

    /**
     * @brief Unserialize a SineOscillator module from the given stringstream
     * @param module_str Stringstream containing the serialized module data
     * @param module_id ID of the module
     * @return Shared pointer to the created SineOscillator module
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);

    /**
     * @brief Process audio data for the SineOscillator module
     * @param frames STK frames object to store the audio data
     * @param streamTime Time in seconds since the audio stream has started
     * @param output_id ID of the output connector (unused in SineOscillator)
     * @return True if audio was processed correctly, false otherwise
     */
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    /**
     * @brief Draw the SineOscillator module UI
     */
    void draw() override;

private:
    stk::SineWave sine; /**< SineWave object used for generating the sine wave */

    /**
     * @brief Update the frequency of the SineOscillator
     * @param frequency New frequency value
     */
    void updateFrequency(float frequency) override;
};

#endif // SINE_OSCILLATOR_H