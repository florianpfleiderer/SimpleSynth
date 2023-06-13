//
// Created by Cheetah on 02.06.2023.
//

#ifndef SIMPLESYNTH_RECTOSCILLATOR_H
#define SIMPLESYNTH_RECTOSCILLATOR_H

#include "Oscillator.h"
#include "BlitSquare.h"

/**
 * @brief Rectangular Oscillator module class
 */
class RectOscillator : public Oscillator {
public:
    /**
     * @brief Default constructor
     * Initialize the RectOscillator with default values
     */
    RectOscillator();

    /**
     * @brief Constructor with parameters
     * Initialize the RectOscillator with the specified module ID, output ID, and frequency
     * @param id Module ID
     * @param id_output Output ID
     * @param frequency Frequency of the oscillator
     */
    RectOscillator(int id, int id_output, float frequency);

    /**
     * @brief Unserialize a RectOscillator module from a stringstream
     * Create a new RectOscillator instance using the serialized data from the stringstream
     * @param module_str Stringstream containing the serialized module data
     * @param module_id ID of the module
     * @return Shared pointer to the created RectOscillator module
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);

    /**
     * @brief Perform the audio processing for the RectOscillator module
     * Generate a rectangular waveform and writes it to the specified output frames
     * @param frames Audio frames to write the generated waveform to
     * @param streamTime Current time in the audio stream
     * @param output_id ID of the output to write to
     * @return True if the audio processing was successful, false otherwise
     */
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    /**
     * @brief Draw the UI representation of the RectOscillator module
     * This function is called to render the module's UI representation in the user interface
     */
    void draw() override;

private:
    stk::BlitSquare rectangle; /**< BlitSquare object for generating rectangular waveforms */

    /**
     * @brief Update the frequency of the RectOscillator
     * Set the frequency of the rectangular waveform generator
     * @param frequency New frequency value
     */
    void updateFrequency(float frequency) override;
};

#endif //SIMPLESYNTH_RECTOSCILLATOR_H
