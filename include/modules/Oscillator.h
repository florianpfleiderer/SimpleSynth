//
// Created by Robert Ristic on 16.05.23.
//

#ifndef SIMPLESYNTH_OSCILLATOR_H
#define SIMPLESYNTH_OSCILLATOR_H

#include "Module.h"
#include <regex>

class Oscillator : public Module {
public:
    Oscillator(std::string name);
    Oscillator(std::string name, int id, int id_output, float frequency);

    void draw() override;

    /**
     * @brief sets the _frequency variable and updates the frequency with te specific stk function
     * 
     * @param freq new frequency
     */
    virtual void updateFrequency(float freq) = 0;

    void serialize_settings(std::ostream &ostream) override;
    static void getSettingsFromText(std::stringstream &module_str, int &id_output, float &frequency);

    ~Oscillator() override;
protected:
    int _id_output;
    float _frequency;
};

#endif // OSCILLATOR_H