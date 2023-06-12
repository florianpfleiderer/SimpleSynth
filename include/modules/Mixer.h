//
// Created by Moritz Mairhofer on 30.05.23.
//

#ifndef SIMPLESYNTH_MIXER_H
#define SIMPLESYNTH_MIXER_H

#include "Module.h"

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

    //! A member function for creating the node GUI
    void draw() override;
};

#endif