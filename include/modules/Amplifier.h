//
// Created by Moritz Mairhofer on 30.05.23.
//

#ifndef SIMPLESYNTH_AMPLIFIER_H
#define SIMPLESYNTH_AMPLIFIER_H
#endif

#include "Module.h"

#include "Stk.h"

//! Amplifier class
/*!
 *  This class represents an amplifier which amplifies the audio signal by multiplying
 *  the numerical (StkFloat) values, that represent the audio signal, with a customizable
 *  constant .
 */
class Amplifier : public Module {

public:
    /*! Amplifier constructor
     *
     * @param Default gain factor for amplifying the audio signal
     */
    Amplifier(unsigned int _gain = 5);

    //! This function is called every frame to draw the module ui.
    void draw() override;

    //! Function used for audio processing
    /*!
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
     * The StkFloat values which represent the audio signal are multiplied by the gain factor.
     *
     * @param frames vector of audio data
     * @param g gain factor
     */
    void amplify(stk::StkFrames& frames, unsigned int g);

    //! Set requested value for gain
    /*!
     *
     * @param g gain factor which is used for multiplying the audio data
     */
    void setGain(unsigned int g);

    void serialize_settings(std::ostream &ostream) override;

    /**
     * @brief Destructor
     */
    virtual ~Amplifier();

protected:
    int _id_output;         /**< ID of the output pin (connector) */
    int _id_input;          /**< ID of the input pin (connector) */
    float _gain;            /**< Gain factor by which the audio signal is amplified */
    int _id_gain;           /**< ID of the gain parameter */


};

