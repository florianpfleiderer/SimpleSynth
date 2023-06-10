//
// Created by Moritz Mairhofer on 30.05.23.
//

#ifndef SIMPLESYNTH_AMPLIFIER_H
#define SIMPLESYNTH_AMPLIFIER_H

#include "Module.h"
#include "Stk.h"

//! Amplifier class
/*!
  TO DO: Amplifier class description
*/
class Amplifier : public Module {
    //! Input pin variable
    int _id_output;
    //! Output pin variable
    int _id_input;
public:

    /**
     * @brief Constructor
     */
    Amplifier();

    /**
     * @brief Draw the module
     * This function is called every frame to draw the module ui.
     */
    void draw() override;

    /**
     * @brief Function used for audio processing
     *
     * * check if all inputs are connected
     * * call tick functions of connected modules
     * * do the necessary calculations
     *
     * @param buffer vector of audio data
     * @param nBufferFrames buffer size
     * @param streamTime time in seconds since the audio stream has started
     * @param output_id output id of the connected module (only used if module has multiple outputs)
     *
     * @return true if audio was processed correctly (else false)
     */
    bool tick(stk::StkFrames& frames, double streamTime, int output_id) override;
    //! Amplify a pending signal
    void amplify(stk::StkFrames& frames);

};

#endif
