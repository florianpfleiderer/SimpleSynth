//
// Created by Cheetah on 08.06.2023.
//

#ifndef SIMPLESYNTH_SAWOSCILLATOR_H
#define SIMPLESYNTH_SAWOSCILLATOR_H

#include "Oscillator.h"
#include "Stk.h"
#include "BlitSaw.h"

class SawOscillator : public Oscillator {
public:
    SawOscillator();

    /**
     * @brief Construct a new SawOscillator object with full controll
     * 
     * @param id id of the module
     * @param id_output id of the output
     * @param frequency frequency of the sawwave
     */
    SawOscillator(int id, int id_output, float frequency);


     /**
     * @brief creates a SawOscillator object from the given module string of the save-file
     * 
     * @param module_str SawOscillator module string from the save-file
     * @param module_id id of the SawOscillator object
     * @return std::shared_ptr<Module> to unserialized SawOscillator object
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
    void draw() override;

private:
    stk::BlitSaw saw;

    void updateFrequency(float frequency) override;
};

#endif //SIMPLESYNTH_SAWOSCILLATOR_H
