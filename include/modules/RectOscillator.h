//
// Created by Cheetah on 02.06.2023.
//

#ifndef SIMPLESYNTH_RECTOSCILLATOR_H
#define SIMPLESYNTH_RECTOSCILLATOR_H

#include "Oscillator.h"
#include "BlitSquare.h"

class RectOscillator : public Oscillator {
public:
    RectOscillator();

    /**
     * @brief Construct a new RectOscillator object with full controll
     * 
     * @param id id of the module
     * @param id_output id of the output
     * @param frequency frequency of the sinewave
     */
    RectOscillator(int id, int id_output, float frequency);


     /**
     * @brief creates a RectOscillator object from the given module string of the save-file
     * 
     * @param module_str RectOscillator module string from the save-file
     * @param module_id id of the RectOscillator object
     * @return std::shared_ptr<Module> to unserialized RectOscillator object
     */
    static std::shared_ptr<Module> unserialize(std::stringstream& module_str, int module_id);

    bool tick(stk::StkFrames &frames, double streamTime, int output_id) override;
    void draw() override;

private:
    stk::BlitSquare rectangle;

    void updateFrequency(float freqency) override;
};

#endif //SIMPLESYNTH_RECTOSCILLATOR_H
