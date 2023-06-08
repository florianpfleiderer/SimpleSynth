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
    //! Amplifier constructor.
    /*!
      TO DO
    */
    Amplifier();

    //! Create the node GUI
    void draw() override;
    //! Amplify a pending signal
    void amplify();

};

#endif
