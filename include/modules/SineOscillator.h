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
     * @brief Construct a new SineOscillator object with full controll
     * 
     * @param id id of the module
     * @param id_output id of the output
     * @param frequency frequency of the sinewave
     */
    SineOscillator(int id, int id_output, float frequency);

    /**
     * @brief creates a SineOscillator object from the given module string of the save-file
     * 
     * @param module_str SineOscillator module string from the save-file
     * @param module_id id of the SineOscillator object
     * @return std::shared_ptr<Module> to unserialized SineOscillator object
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