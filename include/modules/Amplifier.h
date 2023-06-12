//
// Created by Moritz Mairhofer on 30.05.23.
//

#ifndef SIMPLESYNTH_AMPLIFIER_H
#define SIMPLESYNTH_AMPLIFIER_H

#include "Module.h"
#include "Stk.h"

//! Amplifier class
/*!
 *  This class represents an amplifier which amplifies the audio signal by multiplying
 *  the numerical (StkFloat) values, that represent the audio signal, with a customizable
 *  constant .
 */
class Amplifier : public Module {
    //! Output pin variable
    int _id_output;
    //! Input pin variable
    int _id_input;
    //! gain factor
    unsigned int _gain;

public:
    /*! Amplifier constructor
     *
     * @param gain value for amplifying the audio signal
     */
    explicit Amplifier(unsigned int gain = 10);

    //! This function is called every frame to draw the module ui.
    void draw() override;

    /*!  \brief Function used for audio processing
     *
     * check if all inputs are connected
     * call tick functions of connected modules
     * do the necessary calculations
     *
     * @param frames vector of audio data
     * @param streamTime time in seconds since the audio stream has started
     * @param output_id output id of the connected module (only used if module has multiple outputs)
     *
     * @return true if audio was processed correctly (else false)
     */
    bool tick(stk::StkFrames& frames, double streamTime, int output_id) override;

    //! Amplify a pending signal
    /*!
     *
     * @param frames vector of audio data
     */
    void amplify(stk::StkFrames& frames);

    //! Set requested value for gain
    /*!
     *
     * @param g gain factor which is used for multiplying the audio data
     */
    void setGain(unsigned int g);

};

#endif
