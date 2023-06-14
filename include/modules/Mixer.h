//
// Created by Moritz Mairhofer on 30.05.23.
//

#ifndef SIMPLESYNTH_MIXER_H
#define SIMPLESYNTH_MIXER_H

#include "Module.h"
#include "Stk.h"

//! Mixer class
/*!
 * This class overlays the received audio signals from different modules. This happens by
 * superimposing the audio data. The audio data is represented by values of type StkFloat.
 * These values are added together to create the mixed audio signal.
 */
class Mixer : public Module {

public:
    //! Mixer constructor.
    /*!
     *
     */
    Mixer();

    //! Create the GUI of the node
    void draw() override;
    //! Mix the signals pending on input 1 and input 2
    /*!
     *
     * @param audio_signal_1 vector of audio data, signal 1
     * @param audio_signal_2 vector of audio data, signal 2
     * @return the superposition of the two signals
     */
    stk::StkFrames mix(stk::StkFrames& audio_signal_1, stk::StkFrames& audio_signal_2);

    virtual bool tick(stk::StkFrames& frames, double streamTime, int output_id) override;

    void serialize_settings(std::ostream &ostream) override;

    /**
     * @brief Destructor
     */
    virtual ~Mixer();

protected:
    int _id_output;             /**< ID of the output pin (connector) */
    int _id_input_1;            /**< ID of the input pin 1 (connector) */
    int _id_input_2;            /**< ID of the input pin 2 (connector) */
};

#endif