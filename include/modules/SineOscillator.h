//
// Created by Theresa Freibauer on 31.05.2023.
//
#ifndef SINE_OSCILLATOR_H
#define SINE_OSCILLATOR_H

#include "Oscillator.h"
#include "Stk.h"
#include "SineWave.h"

class SineOscillator : public Oscillator {
public:
    SineOscillator();

    /**
     * @brief Construct a new SineOscillator object with full controll
     * 
     * @param id id of the module
     * @param id_output id of the output
     * @param frequency frequency of the sinewave
     */
    SineOscillator(int id, int id_output, float frequency);

    /**
     * @brief creates a SineOscillator object from the given module string of the save-file
     * 
     * @param module_str SineOscillator module string from the save-file
     * @param module_id id of the SineOscillator object
     * @return std::shared_ptr<Module> to unserialized SineOscillator object
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);
    
    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
    void draw() override;

private:
    stk::SineWave sine;

    void updateFrequency(float freqency) override;
};

#endif // SINE_OSCILLATOR_H