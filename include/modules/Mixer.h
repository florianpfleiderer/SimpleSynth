//
// Created by Moritz Mairhofer on 30.05.23.
//

#ifndef SIMPLESYNTH_MIXER_H
#define SIMPLESYNTH_MIXER_H

#include "Module.h"

//! Mixer class
/*!
  TO DO: Mixer class description
*/
class Mixer : public Module {
    //! Input pin variable
    int _id_output;
    //! Output pin variable
    int _id_input;
public:
    //! Mixer constructor.
    /*!
      TO DO
    */
    Mixer();

    //! A member function for creating the node GUI
    void draw() override;
};

#endif