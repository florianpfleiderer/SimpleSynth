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
    //! Output pin variable
    int _id_output;
    //! Input pin variables
    int _id_input_1;
    int _id_input_2;

public:
    //! Mixer constructor.
    /*!
     *
     */
    Mixer();

    Mixer(int module_id, int id_output, int id_input_1, int id_input_2);

    //! Create the GUI of the node
    void draw() override;
    //! Mix the signals pending on input 1 and input 2
    stk::StkFrames mix(stk::StkFrames& audio_signal_1, stk::StkFrames& audio_signal_2);

    virtual bool tick(stk::StkFrames& frames, double streamTime, int output_id) override;

    void serialize_settings(std::ostream &ostream) override;
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);
};

#endif