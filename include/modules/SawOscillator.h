//
// Created by Cheetah on 08.06.2023.
//

#ifndef SIMPLESYNTH_SAWOSCILLATOR_H
#define SIMPLESYNTH_SAWOSCILLATOR_H

#include "Oscillator.h"
#include "Stk.h"
#include "BlitSaw.h"

/**
 * @brief Saw Oscillator module that generates a sawtooth waveform
 */
class SawOscillator : public Oscillator {
public:
    /**
     * @brief Default constructor
     * Construct a SawOscillator with default values
     */
    SawOscillator();

    /**
     * @brief Construct a new SawOscillator object with full controll
     * 
     * @param id id of the module
     * @param id_output id of the output
     * @param frequency frequency of the sawwave
     */
    SawOscillator(int id, int id_output, float frequency);


     /**
     * @brief creates a SawOscillator object from the given module string of the save-file
     * 
     * @param module_str SawOscillator module string from the save-file
     * @param module_id id of the SawOscillator object
     * @return std::shared_ptr<Module> to unserialized SawOscillator object
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);

    /**
     * @brief Processe audio data for the SawOscillator module
     * Generate the sawtooth waveform and fills the provided frames with audio samples
     * @param frames StkFrames object to fill with audio samples
     * @param streamTime Time in seconds since the audio stream has started
     * @param output_id ID of the connected output module (unused in this implementation)
     * @return True if audio was processed successfully, false otherwise
     */
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    /**
     * @brief Draw the user interface for the SawOscillator module
     * This function is called every frame to draw the module's UI
     */
    void draw() override;
    bool play(bool state) override;

private:
    stk::BlitSaw saw;   /**< BlitSaw object used to generate the sawtooth waveform */

    /**
     * @brief Update the frequency of the SawOscillator module
     * Set the frequency of the sawtooth waveform to the specified value
     * @param frequency New frequency value
     */
    void updateFrequency(float frequency) override;
};

#endif //SIMPLESYNTH_SAWOSCILLATOR_H
