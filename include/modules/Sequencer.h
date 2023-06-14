//
// Created by Dennis Waniek on 31.05.2023.
//

#ifndef SIMPLESYNTH_SEQUENCER_H
#define SIMPLESYNTH_SEQUENCER_H

#include "Module.h"
#include <algorithm>
#include "Stk.h"

#define INPUT_SIZE 4

class Sequencer : public Module {
private:
    const int _id_bpm;
    const int _id_output;
    std::vector<int> _ids_input;
    int _bpm = 60;
    //[[maybe_unused]] int _selected_bpm = 1;

public:
    Sequencer(unsigned int input_size = 4);

    /**
     * @brief Construct a new Sequencer object with full controll (for load function)
     *
     * @param module_id
     * @param id_output
     * @param id_bpm
     * @param bpm
     * @param ids_input
     */
    Sequencer(int module_id, int id_output, int id_bpm, int bpm, std::vector<int> ids_input);

    ~Sequencer() override;

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;

    void draw() override;
    bool play(bool state) override;

    void serialize_settings(std::ostream &ostream) override;

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