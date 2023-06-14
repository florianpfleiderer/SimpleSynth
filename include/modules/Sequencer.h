//
// Created by Dennis Waniek on 31.05.2023.
//

#ifndef SIMPLESYNTH_SEQUENCER_H
#define SIMPLESYNTH_SEQUENCER_H

#include "Module.h"
#include <algorithm>
#include "Stk.h"

/**
* @brief Step-Sequencer Module
* @details This module takes several inputs and periodically switches between them according to the beats per minute set
*
* @param _id_bpm id for ImNodes slider
* @param _id_output id for ImNode output connector
* @param _ids_input std::vector with ids for ImNode input connectors
* @param _bpm beats per minute
*/
class Sequencer : public Module {

private:
    const int _id_bpm;
    const int _id_output;
    std::vector<int> _ids_input;
    int _bpm = 60;

public:

    /**
     * @brief Construct a new Sequencer object with variable input size
     *
     * @param input_size number of input ports
     */
    Sequencer(unsigned int input_size = 4);

    /**
     * @brief Construct a new Sequencer object with full control (for load function)
     *
     * @param module_id
     * @param id_output
     * @param id_bpm
     * @param bpm
     * @param ids_input
     */
    Sequencer(int module_id, int id_output, int id_bpm, int bpm, std::vector<int> ids_input);

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    void draw() override;

    bool play(bool state) override;

    void serialize_settings(std::ostream &ostream) override;

    /**
     * @brief calculate the currently active step according to the stream time
     *
     * @param streamTime time in seconds since the audio stream has started
     */
    int calc_step_index(double streamTime);

    /**
     * @brief creates a Sequencer object from the given module string of the save-file
     *
     * @param module_str Sequencer module string from the save-file
     * @param module_id id of the Sequencer object
     * @return std::shared_ptr<Module> to unserialized Sequencer object
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);
};

#endif //SIMPLESYNTH_SEQUENCER_H